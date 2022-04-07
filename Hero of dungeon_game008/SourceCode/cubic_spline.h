//
// 2015.8.18
// Mugichoko
//
#ifndef _CUBIC_SPLINE_H_
#define _CUBIC_SPLINE_H_
#include <iostream>
using namespace std;
//#include <opencv2/opencv.hpp>
struct CubicSplineCoeff
{
	float a, b, c, d;
};
//
// Ref. 1: http://www.ipc.akita-nct.ac.jp/yamamoto/lecture/2003/5E/lecture_5E/Lagrange_Spline.pdf
//
template<typename vec2D>
class CubicSpline
{
private:
	vector<CubicSplineCoeff> m_vCoeff;
	vector<vec2D> m_vData;
	float calc_h(unsigned int idx)
	{
		return this->m_vData[idx + 1].x - this->m_vData[idx].x;
	}
	float calc_v(unsigned int idx)
	{
		assert(idx > 0);
		return (6.0f * ((this->m_vData[idx + 1].y - this->m_vData[idx].y) / calc_h(idx)
			- (this->m_vData[idx].y - this->m_vData[idx - 1].y) / calc_h(idx - 1)));
	}
public:
	CubicSpline(
		const vector<vec2D> &vData = vector<vec2D>()
	)
	{
		// Error handling
		const unsigned int n = unsigned int(vData.size());
		assert(n >= 2);
		// Copy the data
		this->m_vData.resize(n);
		copy(vData.begin(), vData.end(), this->m_vData.begin());
		// Set data to a matrix A
		cv::Mat A = cv::Mat::zeros(n, n, CV_32F);
		cv::Mat b(n, 1, CV_32F);
		A.at<float>(0, 0) = 1.0f;
		b.at<float>(0, 0) = 0.0f;
		for (unsigned int r = 1; r < n - 1; ++r)
		{
			A.at<float>(r, r - 1) = calc_h(r - 1);
			A.at<float>(r, r + 1) = calc_h(r);
			A.at<float>(r, r) = 2.0f * (A.at<float>(r, r - 1) + A.at<float>(r, r + 1));
			b.at<float>(r, 0) = this->calc_v(r);
		}
		A.at<float>(n - 1, n - 1) = 1.0f;
		b.at<float>(n - 1, 0) = 0.0f;
		// Calculate parameters c_i
		cv::Mat u = A.inv(cv::DECOMP_LU) * b;
		// Calculate coefficients
		this->m_vCoeff.resize(n - 1);
		for (unsigned int idx = 0; idx < this->m_vCoeff.size(); ++idx)
		{
			this->m_vCoeff[idx].b = u.at<float>(idx, 0) / 2.0f;
			this->m_vCoeff[idx].a =
				(u.at<float>(idx + 1, 0) - u.at<float>(idx))
				/ (6.0f * (this->m_vData[idx + 1].x - this->m_vData[idx].x));
			this->m_vCoeff[idx].d = this->m_vData[idx].y;
			this->m_vCoeff[idx].c =
				(this->m_vData[idx + 1].y - this->m_vData[idx].y) / (this->m_vData[idx + 1].x - this->m_vData[idx].x)
				- (this->m_vData[idx + 1].x - this->m_vData[idx].x) * (2.0f * u.at<float>(idx, 0) + u.at<float>(idx + 1, 0)) / 6.0f;
		}
	}
	~CubicSpline()
	{
	}
	vec2D getValue(
		unsigned int idx,
		float ratio)
	{
		// Error handling
		assert(ratio >= 0.0f && ratio <= 1.0f);
		assert(idx + 1 < this->m_vData.size());
		vec2D v2;
		v2.x = ratio * this->m_vData[idx + 1].x + (1.0f - ratio) * this->m_vData[idx].x;
		float tmp = v2.x - this->m_vData[idx].x;
		v2.y = this->m_vCoeff[idx].a * tmp * tmp * tmp
			+ this->m_vCoeff[idx].b * tmp * tmp
			+ this->m_vCoeff[idx].c * tmp
			+ this->m_vCoeff[idx].d;
		return v2;
	}
};
#endif // !_CUBIC_SPLINE_H_