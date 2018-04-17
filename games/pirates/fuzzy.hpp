class Fuzzy {
	public:
			static float AND(float A, float B) { return (A < B) ? A : B; } //returns logical AND, this is equivalent to finding the minimum
			static float OR(float A, float B) { return (A > B) ? A : B; } //returns logical OR, this is equivalent to finding the max
			static float NOT(float x) { return (1.0f - x); } //this is equivalent to doing a !=
			static float Grade(float x, float lowerThreshold, float upperThreshold); //return 0 is <= to lowerThreshold, returns 1 if >= upperThreshold, returns an upward slope value if in between
			static float Triangle(float x, float m, float lowerThreshold, float upperThreshold); //like grade, but the in between value will be a downward slope value is over m
};

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
