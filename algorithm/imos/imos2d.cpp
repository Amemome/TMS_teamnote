#include <bits/stdc++.h>
using namespace std;

int rect_img[2502][2502];
int diag_img[2502][2502];
int W, H;

// mark start/terminal points on a rectangular basis.
void mark_rect(int px, int py, int qx, int qy)
{
	rect_img[py][px]++;
	rect_img[py][qx+1]--;
	rect_img[qy+1][px]--;
	rect_img[qy+1][qx+1]++;
}

// mark start/terminal points on a diagonal basis.
void mark_diag(int px, int py, int r)
{
	diag_img[py][px-r]++;

	if (py+r+1 < H)
		diag_img[py+r+1][px+1]--;
	else
		diag_img[py+r][px+2]--;

	if (py-r-1 >= 0)
		diag_img[py-r-1][px+1]--;

	diag_img[py][px+r+2]++;
}

// rectangular imos sweeping.
void sweep_rect()
{
	// sweep from left to right.
	for (int i = 0; i < H; i++)
	{
		for (int j = 1; j < W; j++)
			rect_img[i][j] += rect_img[i][j-1];
	}

	// sweep from top to bottom.
	for (int i = 1; i < H; i++)
	{
		for (int j = 0; j < W; j++)
			rect_img[i][j] += rect_img[i-1][j];
	}
}

// diagonal imos sweeping.
void sweep_diag()
{
	// sweep diagonally from bottom-left to top-right.
	for (int i = 1; i < H; i++)
	{
		for (int j = 1; i-j >= 0 && j < W; j++)
			diag_img[i-j][j] += diag_img[i-j+1][j-1];
	}

	for (int i = 1; i < W-1; i++)
	{
		for (int j = 1; j < H && i+j < W; j++)
			diag_img[H-1-j][i+j] += diag_img[H-j][i+j-1];
	}

	// sweep diagonally from top-left to bottom-right.
	for (int i = 0; i < H-1; i++)
	{
		for (int j = 1; i+j < H && j < W; j++)
			diag_img[i+j][j] += diag_img[i+j-1][j-1];
	}

	for (int i = 1; i < W-1; i++)
	{
		for (int j = 1; j < H && i+j < W; j++)
			diag_img[j][i+j] += diag_img[j-1][i+j-1];
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int K;
	cin >> W >> H >> K;

	while (K--)
	{
		// type variable.
		int t;
		cin >> t;

		if (t == 1)
		{
			int px, py, qx, qy;
			cin >> px >> py >> qx >> qy;
			mark_rect(px, py, qx, qy);
		}
		else
		{
			int px, py, r;
			cin >> px >> py >> r;
			mark_diag(px, py, r);
			mark_diag(px, py, r-1);
		}
	}

	sweep_rect();
	sweep_diag();

	// final output.
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			int __value = rect_img[i][j] + diag_img[i][j];
			cout << (__value % 2 ? '#' : '.');
		}

		cout << '\n';
	}

	return 0;
}
