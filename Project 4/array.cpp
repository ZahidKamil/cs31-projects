#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;
const int BAD_ARG = -1;

int tally(const string a[], int n, string target)
{
	int count = 0;
	if (n < 0)
		return BAD_ARG;
	for (int i = 0; i < n; i++)
	{
		if (target == a[i])
			count++;
	}
	return count;
}

int findMatch(const string a[], int n, string target)
{
	if (n < 0)
		return BAD_ARG;
	for (int i = 0; i < n; i++)
	{
		if (a[i] == target)
			return i;
	}
	return BAD_ARG;
}

bool findRun(const string a[], int n, string target, int& begin, int& end)
{
	if (n < 0)
		return false;
	for (int i = 0; i < n - 1; i++)
	{
		if (a[i] == target)
		{
			begin = i;
			if (a[i + 1] != target)
			{
				end = i;
				return true;
			}
			for (int k = i + 1; k < n; k++)
			{
				if (a[k] != target)
				{
					end = k;
					return true;
				}
			}
		}
	}
	return false;
}

int positionOfMin(const string a[], int n)
{
	if (n < 0)
		return BAD_ARG;
	int position;
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		string temp = a[i];
		for (int j = 0; j < n; j++)
		{
			if (temp <= a[j])
				count++;
		}
		if (count == n)
			return i;
		count = 0;
	}
	return -1;
}

int moveToEnd(string a[], int n, int pos)
{
	if (n < 0)
		return BAD_ARG;
	else if (pos < 0)
		return -1;
	else if (pos == n - 1)
		return pos;
	string temp = a[pos];
	for (int i = pos; i < n - 1; i++)
	{
		string temp2 = a[i + 1];
		a[i] = temp2;
	}
	a[n - 1] = temp;
	return pos;
}

int moveToBeginning(string a[], int n, int pos)
{
	if (n < 0)
		return BAD_ARG;
	else if (pos < 0)
		return -1;
	else if (pos == 0)
		return pos;
	string temp = a[pos];
	for (int i = pos; i >= 1; i--)
	{
		string temp2 = a[i - 1];
		a[i] = temp2;
	}
	a[0] = temp;
	return pos;
}

int findDifference(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0)
		return BAD_ARG;
	else if (n2 < 0)
		return BAD_ARG;
	else if (n1 == 0 || n2 == 0)
		return 0;
	else if (n1 > n2)
	{
		for (int i = 0; i < n1; i++)
		{
			if (a1[i] != a2[i])
				return i;
		}
		return n2;
	}
	else if (n1 < n2)
	{
		for (int i = 0; i < n1; i++)
		{
			if (a1[i] != a2[i])
				return i;
		}
		return n1;
	}
	else
	{
		for (int i = 0; i < n1; i++)
		{
			if (a1[i] != a2[i])
				return i;
		}
		return n1;
	}
}


bool subsequence(const string a1[], int n1, const string a2[], int n2) // stuck
{
	if (n1 <= 0)
		return false;
	else if (n2 < 0)
		return false;
	else if (n2 == 0)
		return true;
	else if (n1 < n2) // bad arguments
		return false; 
	else
	{
		int count = 0;
		int count2 = 0;
		for (int i = 0; i < n2; i++)
		{
			count++;
		}
		for (int i = 0; i < n2; i++)
		{
			for (int j = i; j < n1; j++)
			{
				if (a2[i] == a1[j])
				{
					count2++;
					break;
				}
			}
		}
		if (count2 == count)
			return true;
		else
			return false;
	}

}
// Helper function for makeMerger
bool isNotDecreasing(const string a[], int n)
{
	for (int k = n - 1; k > 0; k--)
	{
		if (!(a[k] >= a[k - 1]))
			return false;
	}
	return true;
}

int makeMerger(const string a1[], int n1, const string a2[], int n2, string result[], int max) // in progress
{
	if (n1 < 0 || n2 < 0)
		return BAD_ARG;
	else if (max < 0)
		return BAD_ARG;
	else if (max == 0 || (n1 == 0 && n2 == 0))
		return 0;
	else if (n1 + n2 > max)
		return BAD_ARG;
	else if (!isNotDecreasing(a1, n1) || !isNotDecreasing(a2, n2))
		return BAD_ARG;
	else
	{
		// We know that both arrays are now in nondecreasing order
		int numOfElementsPlaced = n1 + n2;
		int pos = 0;
		for (int k = 0; k < n1; k++, pos++)
			result[pos] = a1[k];
		for (int k = 0; k < n2; k++, pos++)
			result[pos] = a2[k];
		while (!isNotDecreasing(result, pos))
		{
			string str = "";
			for (int k = 0; k < pos - 1; k++)
			{
				if (result[k] > result[k + 1])
				{
					str = result[k];
					result[k] = result[k + 1];
					result[k + 1] = str;
				}
			}
		}
		return numOfElementsPlaced;
	}
}


int separate(string a[], int n, string separator)
{
	string result[10000];
	int k = 0;
	for (int i = 0; i < n; i++)
	{
		if (a[i] < separator)
		{
			result[k] = a[i];
			k++;
		}
	}
	for (int i = 0; i < n; i++)
	{
		if (a[i] == separator)
		{
			result[k] = a[i];
			k++;
		}
	}
	for (int i = 0; i < n; i++)
	{
		if (a[i] > separator)
		{
			result[k] = a[i];
			k++;
		}
	}
	for (int i = 0; i < n; i++)
	{
		a[i] = result[i];
	}
	for (int i = 0; i < n; i++)
	{
		if (!(result[i] < separator))
			return i;
	}
	return n;
}


int eliminateDups(string a[], int n)
{
	if (n < 0)
		return BAD_ARG;
	else if (n == 0)
		return 0;
	else
	{
		int deletedDups = 0;
		int i = 0;
		while (i < n - 1)
		{
			bool othersEqual = true;
			for (int k = i; k < n - 1; k++)
			{
				if (a[k] != a[k + 1])
					othersEqual = false;
			}
    
			if (othersEqual == false && a[i] == a[i + 1])
			{
				deletedDups++;
				for (int k = i + 1; k < n - 1; k++)
				{
					a[k] = a[k + 1];
					// all subsequent items are moved one position to the left
				}
				continue;
			}
			i++;
		}
		return (n - 1) - deletedDups;
	}
}

	int main()
	{
		string h[7] = { "romanoff", "thor", "rogers", "banner", "", "parker", "rogers" };
		assert(tally(h, 7, "rogers") == 2);
		assert(tally(h, 7, "") == 1);
		assert(tally(h, 7, "rhodes") == 0);
		assert(tally(h, 0, "rogers") == 0);
		assert(findMatch(h, 7, "rogers") == 2);
		assert(findMatch(h, 2, "rogers") == -1);
		int bg;
		int en;
		assert(findRun(h, 7, "banner", bg, en) && bg == 3 && en == 3);

		string g[4] = { "romanoff", "thor", "banner", "parker" };
		assert(positionOfMin(g, 4) == 2);
		assert(findDifference(h, 4, g, 4) == 2);
		assert(subsequence(h, 7, g, 4));
		assert(moveToEnd(g, 4, 1) == 1 && g[1] == "banner" && g[3] == "thor");

		string f[4] = { "parker", "banner", "thor", "rogers" };
		assert(moveToBeginning(f, 4, 2) == 2 && f[0] == "thor" && f[2] == "banner");

		string e[5] = { "parker", "parker", "parker", "thor", "thor" };
		assert(eliminateDups(e, 5) == 2 && e[1] == "thor");

		string x[4] = { "rhodes", "rhodes", "tchalla", "thor" };
		string y[4] = { "banner", "parker", "rhodes", "rogers" };
		string z[10];
		assert(makeMerger(x, 4, y, 4, z, 10) == 8 && z[5] == "rogers");

		assert(separate(h, 7, "rogers") == 3);

		cout << "All tests succeeded" << endl;
	}