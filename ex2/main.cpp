#include <sstd/sstd.hpp>

std::vector<double> gen_vecSin(double sample_per_mm, double A, double k, double x_begin, double x_end, double omega, double time){
	std::vector<double> vecSin( (uint)sample_per_mm*(x_end-x_begin) + 1 );
	for(uint i=0; i<vecSin.size(); i++){
		double x = x_begin + (double) i / sample_per_mm;
		vecSin[i] = A * std::sin( k * x - omega * time );
	}
	return vecSin;
}

void plot_vec(const char* tmpDir, const char* fileName,
			  const char* savepath, const std::vector<double>& vecX, const std::vector<double>& vecY){
	
	sstd::c2py<void> vec2graph(tmpDir, fileName, "vec2graph", "void, const char*, vec<double>, vec<double>");
	vec2graph(savepath, vecX, vecY);
}

int main(){
	printf("■ measureTime_start---------------\n\n"); time_m timem; sstd::measureTime_start(timem);
	
	const char* tmpDir     = "tmpDir";   // tmp dir for c2py
	const char* fileName   = "pyFuncs";  // name of python file
	const char* tmpDir_sin = "./tmpSin"; // tmp dir for sequential img files
	sstd::mkdir(tmpDir_sin);
	
	//---
	
	double frameRate = 25;      // frame rate [frame/sec]
	double Vp =  2;             // phase velocity [mm/sec]
	double lambda = 10;         // wavelength [mm]
	double sample_per_mm = 5;   // physical place resolution
	
	double A = 10;              //   amplitude [mm]
	double k = (2*M_PI)/lambda; // wave number [mm]
	double T = lambda/Vp;       // Vp == lambda / T == k / omega
	double omega = (2*M_PI)/T;  // angular frequency
	
	double x_begin=0, x_end=60; // 0 to 60 mm of x axis.
	
	double timeLength = lambda/Vp;
	uint flameNum = frameRate * timeLength;
	
	// generating a specific physical place of sin wave.
	std::vector<std::vector<double>> vvecSin(flameNum);
	#pragma omp parallel for schedule(static)
	for(uint i=0; i<flameNum; i++){ // i is Correspond to time variation
		vvecSin[i] = gen_vecSin(sample_per_mm, A, k, x_begin, x_end, omega, i/frameRate);
	}
	
	uint xNum = (uint)sample_per_mm*(x_end-x_begin) + 1;
	std::vector<double> vecX(xNum); for(uint i=0; i<vecX.size(); i++){ vecX[i]=(double)i/sample_per_mm; }
	
	// conversion of vecSin to graph img
	#pragma omp parallel for schedule(guided)
	for(uint i=0; i<flameNum; i++){
		plot_vec(tmpDir, fileName, sstd::ssprintf("./%s/sin_%04u.png", tmpDir_sin, i).c_str(), vecX, vvecSin[i]);
	}
	
	//---
	
	// convert imgs to GIF
	const char* savePath = "./sin.gif";
	sstd::c2py<void> imgDir2GIF(tmpDir, fileName, "imgDir2GIF", "void, const char*, const char*, const double");
	imgDir2GIF(savePath, tmpDir_sin, frameRate);
	
	//---
	
	sstd::rm(tmpDir    );
//	sstd::rm(tmpDir_sin);
	
	printf("\n");
	printf("■ measureTime_stop----------------\n");
	sstd::measureTime_stop_print(timem);
	return 0;
}

