class Fuzzy {
	public:
			float AND(float A, float B) { return (A < B) ? A : B; }
			float OR(float A, float B) { return (A > B) ? A : B; }
			float NOT(float x) { return (1.0f - x); }
			float Grade(float x, float lowerThreshold, float upperThreshold);
			float Triangle(float x, float x2, float lowerThreshold, float upperThreshold);
}

float Fuzzy::Grade(float x, float lowerThreshold, float upperThreshold){
	if(x <= lowerThreshold) return 0;
	else if(x >= upperThreshold) return 1.0f;
	return (x-lowerThreshold)/(upperThreshold-lowerThreshold);
}

float Fuzzy::Triangle(float x, float m, float lowerThreshold, float upperThreshold){
	if(x <= lowerThreshold) return 0;
	else if(x >= upperThreshold) return 1.0f;
	else if(x <= m) return (x - lowerThreshold)/(m - lowerThreshold);
	return (upperThreshold - x)/(upperThreshold - m);
}
