#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void matchDimensions(vector<float>& v1, vector<float>& v2)
{
	int nDiff = abs((int)v1.size() - (int)v2.size());
	if (v1.size() >= v2.size())
	{
		// Need to fill v2 with zeroes
		for (int i = 0; i < nDiff; i++)
		{
			v2.push_back(0.0f);
		}
	}
	else
	{
		// Need to fill v1 with zeroes
		for (int i = 0; i < nDiff; i++)
		{
			v1.push_back(0.0f);
		}
	}
}

float mag(const vector<float>& v)
{
	float fMag = 0.0f;
	for (auto& n : v)
	{
		fMag += n * n;
	}

	return sqrtf(fMag);
}

void normalize(vector<float>& v)
{
	float fMag = mag(v);
	for (auto& n : v)
	{
		n /= fMag;
	}
}

int main()
{
	// Getting User Input
	string sYourName;
	string sTheirName;
	
	cout << "Enter your name: ";
	cin >> sYourName;

	cout << "Enter their name: ";
	cin >> sTheirName;

	// Ignore capitalization
	transform(sYourName.begin(), sYourName.end(), sYourName.begin(),
		[](unsigned char c) { return tolower(c); });

	transform(sTheirName.begin(), sTheirName.end(), sTheirName.begin(),
		[](unsigned char c) { return tolower(c); });

	// Converting string to int vectors
	// ASCII :: 0 <= (int)char <= 127
	// for all characters
	vector<float> vYourNameVector;
	vector<float> vTheirNameVector;

	// Convert to a vector, but ignore white spaces
	for (auto& c : sYourName)
	{
		if (c != ' ')
			vYourNameVector.push_back((float)(int)c);
	}
	
	for (auto& c : sTheirName)
	{
		if (c != ' ')
			vTheirNameVector.push_back((float)(int)c);
	}

	normalize(vYourNameVector);
	normalize(vTheirNameVector);

	matchDimensions(vYourNameVector, vTheirNameVector);

	// Dot Product
	// Since these are now both unit vectors, 0.0 <= dp <= 1.0
	float dp = 0.0f;
	for (int i = 0; i < vYourNameVector.size(); i++)
	{
		dp += vYourNameVector[i] * vTheirNameVector[i];
	}
	
	// Calculate percentage
	int nSeed = ((int)(dp * 10000)) & 0xF43C6B31;

	cout << nSeed;

	srand(nSeed);
	int nPercentage = rand() % 101;
	
	cout << "Love: " << nPercentage << "%";

	return 0;
}