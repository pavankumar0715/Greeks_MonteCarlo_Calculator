#include <random>
#include <iostream>
#include <functional>
#include "Greeks.hpp"

using namespace std;

// Create a random number generator
std::default_random_engine generator;
std::normal_distribution<double> distribution(0.0, 1.0);

auto random_generator = std::bind(distribution, generator);

void monteCarloSimulation(double r, double S, double K, double T, double sigma, int numSimulations, char type = 'C')
{
    double dt = T / numSimulations;
    double optionPriceSum = 0.0;
    double deltaSum = 0.0;
    double gammaSum = 0.0;
    double thetaSum = 0.0;
    double vegaSum = 0.0;
    double rhoSum = 0.0;

    for (int i = 0; i < numSimulations; ++i)
    {
        // Generate a random price scenario
        double epsilon = random_generator(); // Generate a random number
        double simulatedPrice = S * exp((r - 0.5 * sigma * sigma) * dt + sigma * sqrt(dt) * epsilon);

        // Calculate option price and Greeks for this scenario
        double optionPrice = blackScholes(r, simulatedPrice, K, T, sigma, type);
        double delta = deltaCalc(r, simulatedPrice, K, T, sigma, type);
        double gamma = gammaCalc(r, simulatedPrice, K, T, sigma, type);
        double theta = thetaCalc(r, simulatedPrice, K, T, sigma, type);
        double vega = vegaCalc(r, simulatedPrice, K, T, sigma, type);
        double rho = rhoCalc(r, simulatedPrice, K, T, sigma, type);

        // Accumulate results
        optionPriceSum += optionPrice;
        deltaSum += delta;
        gammaSum += gamma;
        thetaSum += theta;
        vegaSum += vega;
        rhoSum += rho;
    }

    // Calculate average option price and Greeks
    double averageOptionPrice = optionPriceSum / numSimulations;
    double averageDelta = deltaSum / numSimulations;
    double averageGamma = gammaSum / numSimulations;
    double averageTheta = thetaSum / numSimulations;
    double averageVega = vegaSum / numSimulations;
    double averageRho = rhoSum / numSimulations;

    // Print the results
    cout << "Monte Carlo Simulation Results-" << endl;
    cout << "Average Option Price: " << averageOptionPrice << endl;
    cout << "Average Delta: " << averageDelta << endl;
    cout << "Average Gamma: " << averageGamma << endl;
    cout << "Average Theta: " << averageTheta << endl;
    cout << "Average Vega: " << averageVega << endl;
    cout << "Average Rho: " << averageRho << endl;
}
