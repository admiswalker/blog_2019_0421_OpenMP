#include <sstd/sstd.hpp>

std::string worker(const uint i, const std::string& str){
	uint64 n=0;
	uint64 loopNum = std::pow(1.3, i);
	for(; n<loopNum; n++){
		n++;
	}
	return sstd::ssprintf("%u%s %llu", i, str.c_str(), n);
}

int main(){
	printf("■ measureTime_start---------------\n\n"); time_m timem; sstd::measureTime_start(timem);
	
	uint size = 100;
	std::string str=":";
	std::vector<uint> vecIn(size); for(uint i=0; i<vecIn.size(); i++){ vecIn[i]=i; }
	sstd::printn(vecIn);
	std::vector<std::string> vecOut(size);
	
	#pragma omp parallel for schedule(guided)
	for(uint i=0; i<vecIn.size(); i++){
		vecOut[i] = worker(vecIn[i], str);
	}
	
	sstd::printn(vecOut);
	
	printf("\n");
	printf("■ measureTime_stop----------------\n");
	sstd::measureTime_stop_print(timem);
	return 0;
}

