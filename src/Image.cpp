#include "DSS.hpp"
#include "Image.hpp"
#include "Histogramme.hpp"

using namespace std;

Image::Image(){
	mP=0;
	hist = NULL;
}

Image::Image(const Image& i){
	bitMap=i.bitMap;
	mP=i.mP;
	height=i.height;
	width=i.width;
	maxv=i.maxv;
	*hist = *(i.hist);
}

Pixel& Image::getPixel(int i, int j){
	return bitMap[i+width*j];
}

const Pixel& Image::getPixel(int i, int j) const{
	return bitMap[i+width*j];
}

void Image::inputBitmap(std::istream& in){
	switch (mP) {
		case 1:
			for(auto& p:bitMap){
				p.mr = (uchar)pm_getint(in);
				p.mr = 1-p.mr;
			}
			break;
			
		case 2:
			for(auto& p:bitMap){
				p.mr = (uchar)pm_getint(in);
			}
			break;
		case 3:
			for(auto& p:bitMap){
				p.mr = (uchar)pm_getint(in);
				p.mg = (uchar)pm_getint(in);
				p.mb = (uchar)pm_getint(in);
			}
			break;
		case 4:
			for(auto& p:bitMap){
				p.mr = 1-pm_getrawbyte(in);
			}
			break;
		case 5:
			for(auto& p:bitMap){
				p.mr = pm_getrawbyte(in);
			}
			break;
		case 6:
			for(auto& p:bitMap){
				p.mr = pm_getrawbyte(in);
				p.mg = pm_getrawbyte(in);
				p.mb = pm_getrawbyte(in);
			}
			break;
		default:
			break;
	}
}

void Image::construct(istream& in){
	
	int  ich1, ich2;
	
	/* Reading the "Magic number" */
	ich1 = in.get();
	if (ich1 == EOF)
		pm_erreur( "Error: EOF encountered while reading the header" );
	if (ich1 !='P')
		pm_erreur("Error: the file must start by the character P");
	
	ich2 = in.get();
	if (ich2 == EOF)
		pm_erreur( "Error: EOF encountered while reading the header" );
	
	mP=ich2-'0';
	
	/* Reading the dimensions of the image */
	width = pm_getint(in);
	height = pm_getint(in);
	
	if (mP!=1 && mP!=4)
		maxv = (uchar)pm_getint(in);
	else
		maxv = 1;
	
	bitMap = vector<Pixel> (height * width);
	
	inputBitmap(in);
	
	mP =1 + (mP-1)%3;
	
}

Image::Image(const std::string& file){
	ifstream in(file);
	if (in.fail()){
		pm_erreur("Error: Can't open input file");
	}
	construct(in);
}

Image::Image(istream& in){
	construct(in);
}

Image::Image(uchar p, int w, int h, uchar mv){
	mP=p;
	width=w;
	height=h;
	maxv=mv;
}

uchar Image::choixSeuilPbm(){
	return (maxv/2)+1;
}

void Image::setBitMap(const vector<Pixel> &bm){
	bitMap=bm;
}

void Image::topbm(uchar seuil){
	switch (mP) {
		case 1:
			return;
		case 2:
			break;
		case 3:
			topgm();
			break;
		case 0:
			break;
		default:
			pm_erreur("Format de pixel inconnu");
	}
	for (auto& p:bitMap){
		p.mr = (p.mr<seuil);
	}
	maxv=1;
	mP=1;
}

void Image::topbm(){
	uchar seuil=choixSeuilPbm();
	topbm(seuil);
}

void Image::topgm(){
	switch(mP){
		case 1:
			maxv=255;
			for (auto& p:bitMap){
				p.mr=p.mr*maxv;
			}
			break;
		case 2:
			return;
		case 3:
			for (auto& p:bitMap){
				//Using BT.601 coef
				p.mr= (uchar) (0.299 * (double)p.mr + 0.587 * (double)p.mg + 0.114 * (double)p.mb);
			}
			break;
		case 0:
			break;
		default:
			pm_erreur("Format de pixel inconnu");
	}
	mP=2;
}


void Image::toppm(){
	
	switch (mP) {
		case 1:
			topgm();
			break;
		case 2:
			break;
		case 3:
			return;
		case 0:
			break;
		default:
			pm_erreur("Format de pixel inconnu");
	}
	mP = 3;
}

void Image::print(const string& s, bool binary){
	ofstream out(s);
	if (out.fail()){
		pm_erreur("Error: Can't open output file");
	}
	print(out, binary);
	out.close();
}

void Image::print(ostream& out, bool binary){
	out << "P" << (int)mP+binary*3 << endl;
	out << width << " " << height << endl;
	if (mP!=1 && mP!=4)
		out << (int)maxv << endl;
	if (!binary){
		if (mP == 3){
			for (int j=0; j<height; ++j){
				for (int i=0; i<width; ++i){
					Pixel& p = getPixel(i, j);
					out << (int)p.mr << " " << (int)p.mg << " " << (int)p.mb;
					out << " ";
				}
				out << endl;
			}
		}else if (mP == 1){
			for (int j=0; j<height; ++j){
				for (int i=0; i<width; ++i){
					Pixel& p = getPixel(i, j);
					out << 1-(int)p.mr;
					out << " ";
				}
				out << endl;
			}
		} else {
			for (int j=0; j<height; ++j){
				for (int i=0; i<width; ++i){
					Pixel& p = getPixel(i, j);
					out << (int)p.mr;
					out << " ";
				}
				out << endl;
			}
		}
	}else{
		if (mP == 3){
			for (int j=0; j<height; ++j){
				for (int i=0; i<width; ++i){
					Pixel& p = getPixel(i, j);
					out << p.mr << p.mg << p.mb;
				}
			}
		}else if (mP == 1){
			for (int j=0; j<height; ++j){
				for (int i=0; i<width; ++i){
					Pixel& p = getPixel(i, j);
					out << 1-p.mr;
				}
			}
		} else {
			for (int j=0; j<height; ++j){
				for (int i=0; i<width; ++i){
					Pixel& p = getPixel(i, j);
					out << p.mr;
				}
			}
		}
	}
}

Histogramme* Image::getHisto(){
	return hist;
}

void Image::inverse(){
	if (mP == 3){
		for (auto& p : bitMap){
			p.mr = maxv-p.mr;
			p.mg = maxv-p.mg;
			p.mb = maxv-p.mb;
		}
	} else {
		for (auto& p : bitMap){
			p.mr = maxv-p.mr;
		}
	}
}

void Image::gamma_correction(float gamma){
	vector<int> conv(maxv+1);
	
	float gamma_1 = 1.f / gamma;
	for (int i = 0; i < conv.size(); ++i){
		conv[i] = roundf((conv.size() - 1) * pow((float)i / (float)(conv.size() - 1), gamma_1));
	}
	
	if (mP == 3){
		for (auto& p : bitMap){
			p.mr = conv[p.mr];
			p.mg = conv[p.mg];
			p.mb = conv[p.mb];
		}
	} else {
		for (auto& p : bitMap){
			p.mr = conv[p.mr];
		}
	}
	
}

void Image::linear_interpolation(){
	int min, max;
	
	if (!hist){
		hist = new Histogramme(*this);
	}
	
	for (min=0; min <= maxv && hist->tab[min]==0; ++min);
	
	for (max=maxv; max >= 0 && hist->tab[max]==0; --max);
	
	linear_interpolation(min, max);
}

void Image::linear_interpolation(int a, int b){
	vector<int> conv(maxv + 1);
	
	float var = 1.f / (float)(b - a);
	
	for (int i = 0; i < a; ++i){
		conv[i] = i;
	}
	for (int i = a; i <= b; ++i){
		conv[i] = clampi(roundf((i - a) * maxv * var), 0, 255);
	}
	for (int i = b+1; i < conv.size(); ++i){
		conv[i] = i;
	}
	
	if (mP == 3){
		for (auto& p : bitMap){
			p.mr = conv[p.mr];
			p.mg = conv[p.mg];
			p.mb = conv[p.mb];
		}
	} else {
		for (auto& p : bitMap){
			p.mr = conv[p.mr];
		}
	}
	
		
}

void Image::equalization(){
	uint64_t total=width*height;
	if (!hist){
		hist = new Histogramme(*this);
	}
	
	vector<int> conv(maxv+1);
	uint64_t sum=0;
	
	for (int i=0; i<=maxv; ++i){
		sum+=hist->tab[i];
		conv[i] = roundf((float)(maxv*sum)/(float)(total));
	}
	
	for (auto& p : bitMap){
		p.mr = conv[p.mr];
	}
	
	hist->apply_trans(conv);
	
}

void Image::threshold(int thresh){
	
	for (auto& p : bitMap){
		p.mr = (p.mr >= thresh ? maxv : 0);
	}
	
}

void Image::threshold(){
	threshold(maxv/2);
}

//TODO
void Image::thresholdMinVar(){
	
}

void Image::applyConv(vector<int>& kernel1, vector<int>& kernel2){
	vector<int> kernel(kernel1.size() * kernel2.size());
	for (int i=0; i<kernel1.size(); ++i){
		for (int j=0; j<kernel2.size(); ++j){
			kernel[j+i*kernel2.size()] = kernel2[j] * kernel1[i];
		}
	}
	
	applyConv(kernel, (int) kernel2.size(), (int) kernel1.size());
	
}

void Image::applyConv(vector<int>& kernel, int n, int m){
	vector<Pixel> newbitMap(width*height);
	
	n/=2;
	m/=2;
	
	int div=0;
	for(auto& v : kernel){
		div += v;
	}
	
	if (!div){
		div=1;
	}
	
	if (mP != 3){
		for (int j=0; j<height; ++j){
			for (int i=0; i<width; ++i){
				int r=0;
				for (int k=-m; k <= m; ++k){
					int nk=j+k;
					if (nk < 0){
						nk = -nk - 1;
					} else if (nk >= height){
						nk =  height - k;
					}
					
					for (int l=-n; l <= n; ++l){
						int nl=i+l;
						if (nl < 0){
							nl = -nl - 1;
						} else if (nl >= width){
							nl =  width - l;
						}
						
						Pixel& p = getPixel(nl, nk);
						r += kernel[l+n + (k+m) * (2*n+1)] * (int)p.mr;
					}
				}
				newbitMap[i+j*width].mr = roundf((float)r / (float)div);
			}
		}
	} else {
		for (int j=0; j<height; ++j){
			for (int i=0; i<width; ++i){
				int r=0;
				int g=0;
				int b=0;
				for (int k=-m; k <= m; ++k){
					int nk=j+k;
					if (nk < 0){
						nk = -k - 1;
					} else if (nk >= height){
						nk =  height - k;
					}
					
					for (int l=-n; l <= n; ++l){
						int nl=i+l;
						if (nl < 0){
							nl = -l - 1;
						} else if (nl >= width){
							nl =  width - l;
						}
						
						Pixel& p = getPixel(nl, nk);
						r += kernel[l+n + (k+m) * width] * p.mr;
						g += kernel[l+n + (k+m) * width] * p.mr;
						b += kernel[l+n + (k+m) * width] * p.mr;
					}
				}
				newbitMap[i+j*width].mr = roundf((float)r / (float)div);
				newbitMap[i+j*width].mr = roundf((float)g / (float)div);
				newbitMap[i+j*width].mr = roundf((float)b / (float)div);
			}
		}
	}
	bitMap.swap(newbitMap);
}

int binomial(uint64_t n, uint64_t k){
	uint64_t lim = min(k, n-k);
	
	uint64_t seuil = UINT64_MAX / n;
	
	uint64_t top = 1;
	uint64_t bot = 1;
	
	
	for (long i = 0; i < lim; ++i){
		
		if (top > seuil){
			uint64_t div = gcd(top, bot);
			
			top /= div;
			bot /= div;
		}
		
		top *= n-i;
		bot *= i+1;
		
	}
	
	return (int)(top/bot);
}

void Image::gaussianSmooth(int size){
	vector<int> mat(size);
	
	for (int i=0; i<= size/2; ++i){
		mat[i] = mat[size - i - 1] = binomial(size, i);
	}

	applyConv(mat, mat);
}

void Image::dilate(int size){
	vector<Pixel> newbitMap(width*height);
	int lim = size/2;
	
	for (int j=0; j<height; ++j){
		for (int i=0; i<width; ++i){
		
			uchar maxi = 0;
			for (int k=-lim; k <= lim; ++k){
				int nk = clampi(j+k, 0, height-1);
				for (int l=-lim; l <= lim; ++l){
					int nl = clampi(i+l, 0, width-1);
					maxi =  max(getPixel(nl, nk).mr, maxi);
				}
			}
			newbitMap[i+j*width].mr = maxi;
			
		}
	}
	
	bitMap.swap(newbitMap);
}

void Image::erode(int size){
	vector<Pixel> newbitMap(width*height);
	int lim = size/2;
	
	for (int j=0; j<height; ++j){
		for (int i=0; i<width; ++i){
			
			uchar mini = maxv;
			bool fini = false;
			for (int k=-lim; !fini && k <= lim; ++k){
				int nk = clampi(j+k, 0, height-1);
				for (int l=-lim; !fini && l <= lim; ++l){
					int nl = clampi(i+l, 0, width-1);
					mini =  min(getPixel(nl, nk).mr, mini);
				}
			}
			newbitMap[i+j*width].mr = mini;
			
		}
	}
	
	bitMap.swap(newbitMap);
}

void Image::close(int size){
	dilate(size);
	erode(size);
}

void Image::open(int size){
	erode(size);
	dilate(size);
}

//TODO: CDEGUEU
void Image::sobelNorm(){
	vector<int> newbitMap(bitMap.size()), newbitMap2(bitMap.size());
	
	vector<int> sob1(3), sob2(3);
	sob1[0] = 1;
	sob1[1] = 2;
	sob1[2] = 1;
	
	sob2[0] = 1;
	sob2[1] = 0;
	sob2[2] = -1;
	
	int m=1;
	int n=1;
	
	vector<int> kernel(sob1.size() * sob2.size());
	for (int i=0; i<sob1.size(); ++i){
		for (int j=0; j<sob2.size(); ++j){
			kernel[j+i*sob2.size()] = sob2[j] * sob1[i];
		}
	}
	
	topgm();
	
	//applyConv(sob1, sob2);
	for (int j=0; j<height; ++j){
		for (int i=0; i<width; ++i){
			int r=0;
			for (int k=-m; k <= m; ++k){
				int nk=j+k;
				if (nk < 0){
					nk = -nk - 1;
				} else if (nk >= height){
					nk =  height - k;
				}
				
				for (int l=-n; l <= n; ++l){
					int nl=i+l;
					if (nl < 0){
						nl = -nl - 1;
					} else if (nl >= width){
						nl =  width - l;
					}
					
					Pixel& p = getPixel(nl, nk);
					r += kernel[l+n + (k+m) * (2*n+1)] * (int)p.mr;
				}
			}
			newbitMap[i+j*width] = r;
		}
	}
	
	for (int i=0; i<sob1.size(); ++i){
		for (int j=0; j<sob2.size(); ++j){
			kernel[j+i*sob2.size()] = sob2[i] * sob1[j];
		}
	}
	
	for (int j=0; j<height; ++j){
		for (int i=0; i<width; ++i){
			int r=0;
			for (int k=-m; k <= m; ++k){
				int nk=j+k;
				if (nk < 0){
					nk = -nk - 1;
				} else if (nk >= height){
					nk =  height - k;
				}
				
				for (int l=-n; l <= n; ++l){
					int nl=i+l;
					if (nl < 0){
						nl = -nl - 1;
					} else if (nl >= width){
						nl =  width - l;
					}
					
					Pixel& p = getPixel(nl, nk);
					r += kernel[l+n + (k+m) * (2*n+1)] * (int)p.mr;
				}
			}
			newbitMap2[i+j*width] = r;
		}
	}
	
	for (int i=0; i<bitMap.size(); ++i){
		//TODO: define color depending on the direction of the norm
		bitMap[i].mr = sqrt(newbitMap2[i] * newbitMap2[i] + newbitMap[i] * newbitMap[i]);
	}
	
	/*mP = 3;
	for (int i=0; i<bitMap.size(); ++i){
		int color = bitMap[i].mr;
		if (color != 0){
			bitMap[i].mr = (int)(128*cos(3*color+2)+128);
			bitMap[i].mg = (int)(128*cos(7*color+5)+128);
			bitMap[i].mb = (int)(128*cos(13*color+11)+128);
		}
	}*/
	
}

uint32_t Image::area(bool white=true) {

	uint32_t ans(0);

	for(Pixel p : bitMap) {
		if((!white && p.isBlack()) || (white && !p.isBlack())) {
			++ans;
		}
	}

	return ans;
}

double Image::perimeter(const Domain& d, const DigitalSet& forme){
	return DSSperimeter(d, forme);
}

double Image::area_perimeter_feature() {
	Domain d(Point(-1,-1), Point(width+1, height+1));
	DigitalSet forme(d);
	extractForme(forme);
	double perim = perimeter(d, forme);

	return ((double)forme.size() / perim * perim);
}

//TODO hough and fourier transforms

void Image::printHist(const std::string& s){
	ofstream out(s);
	if (out.fail()){
		pm_erreur("Error: Can't open output file");
	}
	printHist(out);
	out.close();
	
}

void Image::printHist(std::ostream& out){
	if (!hist){
		hist = new Histogramme(*this);
	}
	out << *hist;
}

int find(vector<int>& tab, int i){
	if (tab[i]==i)
		return i;
	return (tab[i] = find(tab, tab[i]));
}

void unif(vector<int>& tab, int i, int j){
	tab[find(tab,i)] = find(tab, j);
}

void Image::comp_connexe(Image& im) const{
	vector<int> tab;
	
	vector<int> compMap(width*height);
	
	im.bitMap = vector<Pixel>(width*height);
	im.width=width;
	im.height=height;
	im.maxv = 255;
	im.mP = 3;
	
	
	for (int j=0; j<height; ++j){
		for (int i=0; i<width; ++i){
			int act=-1;
			for (int l=-1; l<=0; ++l){
				for (int k=-1; k<=0; ++k){
					if ((k || l) && (i+k >= 0 && j+l >= 0)){
						if (getPixel(i, j) == getPixel(i+k, j+l)){
							if (act == -1){
								act = compMap[i+k+width*(j+l)];
							} else {
								unif(tab, act, compMap[i+k+width*(j+l)]);
								act = find(tab, act);
							}
						}
					}
				}
			}
			if (act == -1){
				act = (int)tab.size();
				tab.push_back((int)tab.size());
			}
			compMap[i+width*j] = act;
		}
	}
	
	for (int j=0; j<height; ++j){
		for (int i=0; i<width; ++i){
			int color = find(tab, compMap[i+width*j]);
			im.getPixel(i, j).mr = (int)(128*cos(3*color+2)+128);
			im.getPixel(i, j).mg = (int)(128*cos(7*color+5)+128);
			im.getPixel(i, j).mb = (int)(128*cos(13*color+11)+128);
		}
	}

}


void Image::extractForme(DigitalSet& out){
	for (int j = 0; j < height; ++j){
		for (int i = 0; i < width; ++i){
			if (getPixel(i, j).mr == 1){
				out.insert(Point(i, j));
			}
		}
	}
}


uint32_t Image::raw_moment(uint32_t p, uint32_t q) {

    uint32_t ans(0);
    for(uint32_t x = 0; x < width; ++x) {
        for(uint32_t y = 0; y < height; ++y) {
            ans += pow(x, p) * pow(y, q) * bitMap[x * height + y].mr;
        }
    }

    return ans;
}

double square(double x) {
    return x * x;
}

void Image::compute_moments() {
    /**
     * 0, 0
     * 0, 1
     * 1, 0
     * 1, 1
     * 2, 0
     * 0, 2
     * 2, 1
     * 1, 2
     * 3, 0
     * 0, 3
     */
    uint32_t raw_moments[4][4];

    raw_moments[0][0] = raw_moment(0, 0);
    raw_moments[0][1] = raw_moment(0, 1);
    raw_moments[1][0] = raw_moment(1, 0);
    raw_moments[1][1] = raw_moment(1, 1);
    raw_moments[2][0] = raw_moment(2, 0);
    raw_moments[0][2] = raw_moment(0, 2);
    raw_moments[2][1] = raw_moment(2, 1);
    raw_moments[1][2] = raw_moment(1, 2);
    raw_moments[3][0] = raw_moment(3, 0);
    raw_moments[0][3] = raw_moment(0, 3);

    double centroid_x = raw_moments[1][0] / (double)raw_moments[0][0];
    double centroid_y = raw_moments[0][1] / (double)raw_moments[0][0];

    double moments[4][4];

    moments[0][0] = raw_moments[0][0];
    moments[0][1] = 0;
    moments[1][0] = 0;
    moments[1][1] = raw_moments[1][1] - centroid_x * raw_moments[0][1];
    moments[2][0] = raw_moments[2][0] - centroid_x * raw_moments[1][0];
    moments[0][2] = raw_moments[0][2] - centroid_y * raw_moments[0][1];
    moments[2][1] = raw_moments[2][1] -
            2 * centroid_x * raw_moments[1][1] -
            centroid_y * raw_moments[2][0] +
            2 * square(centroid_x) * raw_moments[0][1];

    moments[1][2] = raw_moments[1][2] -
                    2 * centroid_y * raw_moments[1][1] -
                    centroid_x * raw_moments[0][2] +
                    2 * square(centroid_y) * raw_moments[1][0];

    moments[3][0] = raw_moments[3][0] -
            3 * centroid_x * raw_moments[2][0] +
            2 * square(centroid_x) * raw_moments[1][0];

    moments[0][3] = raw_moments[0][3] -
                    3 * centroid_y * raw_moments[0][2] +
                    2 * square(centroid_y) * raw_moments[0][1];

    double mu_0 = moments[0][0];

    for(uint32_t i = 0; i < 4; ++i) {
        for(uint32_t j = 0; j < 4; ++j) {
            moments[i][j] /= pow(mu_0, 1 + ((i + j) / 2.0));
        }
    }

    hu_moments[0] = moments[2][0] + moments[0][2];

    hu_moments[1] = square(moments[2][0] - moments[0][2]) +
            4 * square(moments[1][1]);

    hu_moments[2] = square(moments[3][0] - 3 * moments[1][2]) +
            square(3 * moments[2][1] - moments[0][3]);

    hu_moments[3] = square(moments[3][0] + moments[1][2]) +
            square(moments[2][1] + moments[0][3]);

    hu_moments[4] =
            (
                    (
                            (moments[3][0] - 3 * moments[1][2]) *
                            (moments[3][0] + moments[1][2])
                    ) *
                            (square(moments[3][0] + moments[1][2])) - 3 *
                            (square(moments[2][1] + moments[0][3]))) +
            (
                    (
                            (3 * moments[2][1] - moments[0][3]) *
                            (moments[2][1] + moments[0][3])
                    ) *
                            (3 * square(moments[3][0] + moments[1][2])) -
                            (square(moments[2][1] + moments[0][3]))
            );

    hu_moments[5] = (moments[2][0] - moments[0][2]) *
            (       square(moments[3][0] + moments[1][2]) -
                    square(moments[2][1] + moments[0][3])
            ) +
            (4 * moments[1][1]) *
                    (moments[3][0] + moments[1][2]) *
                    (moments[2][1] + moments[0][3]);

    hu_moments[6] =
            (
                    (
                            (3 * moments[2][1] - moments[0][3]) *
                            (moments[3][0] + moments[1][2])
                    ) *
                            (square(moments[3][0] + moments[1][2])) - 3 *
                            (square(moments[2][1] + moments[0][3]))) -
            (
                    (
                            (moments[3][0] - 3 * moments[1][2]) *
                            (moments[2][1] + moments[0][3])
                    ) *
                            (3 * square(moments[3][0] + moments[1][2])) -
                    square(moments[2][1] + moments[0][3])
            );
}

std::string Image::getPath() {
    return path;
}


































