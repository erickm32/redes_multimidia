bool codifica(const char *filename, const void *data, int width, int height, int comp, int quality){
	// Encode 8x8 macroblocks
	const unsigned char *imageData = (const unsigned char *)data;
	int DCY=0, DCU=0, DCV=0;
	int bitBuf=0, bitCnt=0;
	int ofsG = comp > 1 ? 1 : 0, ofsB = comp > 1 ? 2 : 0;
	for(int y = 0; y < height; y += 8) {
		for(int x = 0; x < width; x += 8) {
			float YDU[64], UDU[64], VDU[64];
			for(int row = y, pos = 0; row < y+8; ++row) {
				for(int col = x; col < x+8; ++col, ++pos) {
					int p = row*width*comp + col*comp;
					if(row >= height) {
						p -= width*comp*(row+1 - height);
					}
					if(col >= width) {
						p -= comp*(col+1 - width);
					}

					float r = imageData[p+0], g = imageData[p+ofsG], b = imageData[p+ofsB];
					YDU[pos]=+0.29900f*r+0.58700f*g+0.11400f*b-128;
					UDU[pos]=-0.16874f*r-0.33126f*g+0.50000f*b;
					VDU[pos]=+0.50000f*r-0.41869f*g-0.08131f*b;
				}
			}

			DCY = jo_processDU(fp, bitBuf, bitCnt, YDU, fdtbl_Y, DCY, YDC_HT, YAC_HT);
			DCU = jo_processDU(fp, bitBuf, bitCnt, UDU, fdtbl_UV, DCU, UVDC_HT, UVAC_HT);
			DCV = jo_processDU(fp, bitBuf, bitCnt, VDU, fdtbl_UV, DCV, UVDC_HT, UVAC_HT);
		}
	}
	
	return true;
}