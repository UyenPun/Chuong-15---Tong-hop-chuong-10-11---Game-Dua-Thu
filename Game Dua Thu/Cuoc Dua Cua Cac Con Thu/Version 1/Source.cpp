#include <iostream>
#include <fstream> // thư viện hỗ trợ file.
#include <string> // thư viện hỗ trợ chuỗi.
#include <vector>
using namespace std;
#define SUTU_THOIGIANBATDAU 9
#define THO_THOIGIANBATDAU 8
#define RUA_THOIGIANBATDAU 7

#define SUTU_QUANGDUONGCHAY 210
#define THO_QUANGDUONGCHAY 210
#define RUA_QUANGDUONGCHAY 135

// Thông tin 1 con vật
struct ConVat
{
	string MaSo;
	int TocDo, TrangBi;
};
typedef struct ConVat CONVAT;

void NhapConVat(ifstream &FileIn, CONVAT &cv)
{
	FileIn >> cv.MaSo >> cv.TocDo >> cv.TrangBi;
}

void XuatConVat(ofstream &FileOut, CONVAT cv)
{
	FileOut << cv.MaSo << " " << cv.TocDo << " " << cv.TrangBi;
}

void NhapDanhSach(ifstream &FileIn, vector<CONVAT> &DanhSach)
{
	int n;
	FileIn >> n;

	for(int i = 1; i <= n; i++)
	{
		CONVAT cv;
		NhapConVat(FileIn, cv);

		DanhSach.push_back(cv);
	}
}

void XuatDanhSach(ofstream &FileOut, vector<CONVAT> DanhSach)
{
	int n = DanhSach.size();

	for(int i = 0; i < n; i++)
	{
		XuatConVat(FileOut, DanhSach[i]);
		FileOut << endl;
	}
}

int TimVanTocThucSu(CONVAT cv)
{
	if(cv.TrangBi == 0)
	{
		return cv.TocDo;
	}
	else
	{
		if(cv.MaSo[0] == 'L')
		{
			return cv.TocDo * 2;
		}
		else if(cv.MaSo[0] == 'R')
		{
			return cv.TocDo + 30;
		}
		else if(cv.MaSo[0] == 'T')
		{
			return cv.TocDo * 5;
		}
	}
}

double TimThoiGianDiHetQuangDuong(CONVAT cv)
{
	int tocdothucsu = TimVanTocThucSu(cv);

	if(cv.MaSo[0] == 'L')
	{
		return (double)SUTU_QUANGDUONGCHAY / tocdothucsu;
	}
	else if(cv.MaSo[0] == 'T')
	{
		return (double)RUA_QUANGDUONGCHAY / tocdothucsu;
	}
	else if(cv.MaSo[0] == 'R')
	{
		return (double)THO_QUANGDUONGCHAY / tocdothucsu;
	}
}

double TimThoiGianVeDich(CONVAT cv)
{
	double ThoiGianChay = TimThoiGianDiHetQuangDuong(cv);

	if(cv.MaSo[0] == 'L')
	{
		return SUTU_THOIGIANBATDAU + ThoiGianChay;	
	}
	else if(cv.MaSo[0] == 'T')
	{
		return RUA_THOIGIANBATDAU + ThoiGianChay;
	}
	else if(cv.MaSo[0] == 'R')
	{
		return THO_THOIGIANBATDAU + ThoiGianChay;
	}
}

void HoanVi(CONVAT &a, CONVAT &b)
{
	CONVAT Temp = a;
	a = b;
	b = Temp;
}

void SapXepDanhSach(vector<CONVAT> &DanhSach)
{
	int n = DanhSach.size();
	for(int i = 0; i < n - 1; i++)
	{
		for(int j = i + 1; j < n; j++)
		{
			double ThoiGianVeDich_1 = TimThoiGianVeDich(DanhSach[i]);
			double ThoiGianVeDich_2 = TimThoiGianVeDich(DanhSach[j]);

			
				if(ThoiGianVeDich_1 > ThoiGianVeDich_2)
				{
					HoanVi(DanhSach[i], DanhSach[j]);
				}	
			
		}
	}
}

int main()
{
	ifstream FileIn("INPUT.TXT");

	if(!FileIn)
	{
		cout << "\nKhong tim thay tap tin INPUT.TXT";
		system("pause");
		return 0;
	}

	vector<CONVAT> DanhSach;
	NhapDanhSach(FileIn, DanhSach);

	FileIn.close(); // đóng lại.

	ofstream FileOut("OUTPUT.TXT");
	
	// Sap xep tang dan
	SapXepDanhSach(DanhSach);

	int dem = 0;
	int n = DanhSach.size();
	FileOut << "f" << endl;
	for(int i = 0; i < n; i++)
	{
		if(TimThoiGianVeDich(DanhSach[i]) <= 12)
		{
			FileOut << i + 1 << ". ";
			XuatConVat(FileOut, DanhSach[i]);
			FileOut << endl;
			dem++;
		}
	}

	FileOut.seekp(0, SEEK_SET);
	FileOut << dem << endl;

	FileOut.close();

	system("pause");
	return 0;
}