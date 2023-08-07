#include <iostream>
// #include "Greeks.hpp"
#include "MonteCarloSim.hpp"

using namespace std;

void greeks(double r, double S, double K, double T, double sigma, char type)
{
    try
    {

        double optionPrice = blackScholes(r, S, K, T, sigma, type);
        double delta = deltaCalc(r, S, K, T, sigma, type);
        double gamma = gammaCalc(r, S, K, T, sigma, type);
        double vega = vegaCalc(r, S, K, T, sigma, type);
        double theta = thetaCalc(r, S, K, T, sigma, type);
        double rho = rhoCalc(r, S, K, T, sigma, type);

        int decimalPlaces = 3;
        cout << "Option Price: " << customRound(optionPrice, decimalPlaces) << endl;
        cout << "       Delta: " << customRound(delta, decimalPlaces) << endl;
        cout << "       Gamma: " << customRound(gamma, decimalPlaces) << endl;
        cout << "        Vega: " << customRound(vega, decimalPlaces) << endl;
        cout << "       Theta: " << customRound(theta, decimalPlaces) << endl;
        cout << "         Rho: " << customRound(rho, decimalPlaces) << endl;
    }
    catch (exception &e)
    {
        cout << "Error: " << e.what() << endl;
    }
}

void monteCarlo(double r, double S, double K, double T, double sigma, char type)
{
    try
    {
        int numSimulations;
        cout << "Enter the number of simulations: " << endl;
        cin >> numSimulations;
        monteCarloSimulation(r, S, K, T, sigma, numSimulations, type);
    }
    catch (const std::exception &e)
    {
        cout << "Error: " << e.what() << endl;
    }
}

int main()
{
    int choice;
    cout << "1. Greeks" << endl;
    cout << "2. Monte Carlo Simulation" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    double r, S, K, T, sigma;
    char type;
    cout << "Enter the current stock price: " << endl;
    cin >> S;
    cout << "Enter the strike price: " << endl;
    cin >> K;
    cout << "Enter the time to maturity: " << endl;
    cin >> T;
    cout << "Enter the volatility: " << endl;
    cin >> sigma;
    cout << "Enter the risk free interest rate: " << endl;
    cin >> r;
    cout << "Enter the option type (C/P): " << endl;
    cin >> type;
    switch (choice)
    {
    case 1:
        greeks(r, S, K, T, sigma, type);
        break;
    case 2:
        monteCarlo(r, S, K, T, sigma, type);
        break;
    default:
        cout << "Invalid choice" << endl;
    }

    return 0;
}

/*
Value Momentum Cycle


*/