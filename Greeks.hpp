#include <iostream>
#include <cmath>
#include <boost/math/distributions/normal.hpp>

using namespace boost::math;
using namespace std;

double customRound(double value, int decimalPlaces)
{
    double factor = pow(10, decimalPlaces);
    return round(value * factor) / factor;
}

double blackScholes(double r, double S, double K, double T, double sigma, char type = 'C')
{
    // Calculate BlackScholes option price for call/put
    double d1 = (log(S / K) + (r + pow(sigma, 2) / 2) * T) / (sigma * sqrt(T));
    double d2 = d1 - sigma * sqrt(T);

    if (type == 'C')
    {
        double price = S * cdf(normal(), d1) - K * exp(-r * T) * cdf(normal(), d2);
        return price;
    }
    else if (type == 'P')
    {
        double price = K * exp(-r * T) * cdf(normal(), -d2) - S * cdf(normal(), -d1);
        return price;
    }

    throw invalid_argument("Invalid option type");
}

double deltaCalc(double r, double S, double K, double T, double sigma, char type = 'C')
{
    // Calculate delta of option
    double d1 = (log(S / K) + (r + pow(sigma, 2) / 2) * T) / (sigma * sqrt(T));

    if (type == 'C')
    {
        double delta = cdf(normal(), d1);
        return delta;
    }
    else if (type == 'P')
    {
        double delta = -cdf(normal(), -d1);
        return delta;
    }

    throw invalid_argument("Invalid option type");
}

double gammaCalc(double r, double S, double K, double T, double sigma, char type = 'C')
{
    // Calculate gamma of option
    double d1 = (log(S / K) + (r + pow(sigma, 2) / 2) * T) / (sigma * sqrt(T));

    double gamma = pdf(normal(), d1) / (S * sigma * sqrt(T));
    return gamma;
}

double vegaCalc(double r, double S, double K, double T, double sigma, char type = 'C')
{
    // Calculate vega of option
    double d1 = (log(S / K) + (r + pow(sigma, 2) / 2) * T) / (sigma * sqrt(T));

    double vega = 0.01 * S * pdf(normal(), d1) * sqrt(T);
    return vega;
}

double thetaCalc(double r, double S, double K, double T, double sigma, char type = 'C')
{
    // Calculate theta of option
    double d1 = (log(S / K) + (r + pow(sigma, 2) / 2) * T) / (sigma * sqrt(T));
    double d2 = d1 - sigma * sqrt(T);

    if (type == 'C')
    {
        double theta = -S * pdf(normal(), d1) * sigma / (2 * sqrt(T)) - r * K * exp(-r * T) * cdf(normal(), d2);
        return theta / 365;
    }
    else if (type == 'P')
    {
        double theta = -S * pdf(normal(), d1) * sigma / (2 * sqrt(T)) + r * K * exp(-r * T) * cdf(normal(), -d2);
        return theta / 365;
    }

    throw invalid_argument("Invalid option type");
}

double rhoCalc(double r, double S, double K, double T, double sigma, char type = 'C')
{
    // Calculate rho of option
    double d1 = (log(S / K) + (r + pow(sigma, 2) / 2) * T) / (sigma * sqrt(T));
    double d2 = d1 - sigma * sqrt(T);

    if (type == 'C')
    {
        double rho = K * T * exp(-r * T) * cdf(normal(), d2);
        return rho * 0.01;
    }
    else if (type == 'P')
    {
        double rho = -K * T * exp(-r * T) * cdf(normal(), -d2);
        return rho * 0.01;
    }

    throw invalid_argument("Invalid option type");
}
