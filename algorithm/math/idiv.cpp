// computes a/b and prints out p digits after the decimal point (rounded).
void printd(int a, int b, int p)
{
	// int sign = a*b < 0;
	a = abs(a);
	b = abs(b);
	vector<int> digits;

	digits.push_back(a/b);
	a %= b;

	for (int i = 0; i <= p; i++)
	{
		a *= 10;
		digits.push_back(a/b);
		a %= b;
	}

	if (digits[p+1] >= 5)
		digits[p]++;

	for (int i = p; i >= 1; i--)
	{
		if (digits[i] == 10)
		{
			digits[i] = 0;
			digits[i-1]++;
		}
		else
			break;
	}

	// if (sign)
	//	cout << '-';

	cout << digits[0] << '.';
	for (int i = 1; i <= p; i++)
		cout << digits[i];
	cout << '\n';
}
