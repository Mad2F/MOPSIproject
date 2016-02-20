vector<vector<float> > costmatrix(vector<float> X, vector<float> Y){
	vector<vector<float> > Result;
	//Init
	for (int i = 0; i < X.size(); i++){
		vector<float> I;
		I.push_back(1);
		for (int j = 1; j < Y.size(); j++){
			if (i == 0){ I.push_back(1); }
			else{ I.push_back(0); }
		}
		Result.push_back(I);
	}
	//Recurrence
	for (int i = 0; i < X.size(); i++){
		for (int j = 0; j < Y.size(); j++){
			if (i == 0 || j == 0){
				Result[i][j] = 1;
			}
			else{
				Result[i][j] = min(min(Result[i - 1][j - 1], Result[i - 1][j]), Result[i][j - 1]) + cost(X[i], Y[j]);
			}
		}
	}
	return Result;
}