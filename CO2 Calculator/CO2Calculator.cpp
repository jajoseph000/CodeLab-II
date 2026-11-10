
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

int main() {
    double distance;
    double emissionFactor = 0.0;
    double totalEmissions;
    int transport;

    cout << "=================================" << endl;
    cout << "        CO2 CALCULATOR           " << endl;
    cout << "=================================" << endl;

    // Ask the user for travel distance
    cout << "\nEnter travel distance in km: ";
    cin >> distance;

    // Validate distance input
    if (cin.fail() || distance < 0) {
        cout << "Error: Invalid distance!" << endl;
        return 1;
    }

    // Display transport options
    cout << "\nSelect transport type:" << endl;
    cout << "1. Car" << endl;
    cout << "2. Bus" << endl;
    cout << "3. Train" << endl;
    cout << "Enter your choice (1-3): ";
    cin >> transport;

    // Validate transport input
    if (cin.fail()) {
        cout << "Error: Invalid transport choice!" << endl;
        return 1;
    }

    // Demonstration emission factors:
    // kilograms of CO2 per passenger-kilometre.
    // These are illustrative, not verified official factors.
    switch (transport) {
        case 1:
            emissionFactor = 0.17;
            break;

        case 2:
            emissionFactor = 0.10;
            break;

        case 3:
            emissionFactor = 0.04;
            break;

        default:
            cout << "Error: Invalid transport choice!" << endl;
            return 1;
    }

    // Calculate estimated CO2 emissions
    totalEmissions = distance * emissionFactor;

    // Display calculated result
    cout << fixed << setprecision(2);

    cout << "\n=================================" << endl;
    cout << "          CO2 RESULTS            " << endl;
    cout << "=================================" << endl;

    cout << "Distance travelled: "
         << distance << " km" << endl;

    cout << "Emission factor: "
         << emissionFactor << " kg CO2/km" << endl;

    cout << "Total estimated CO2 emissions: "
         << totalEmissions << " kg" << endl;

    cout << "\nCalculation completed successfully!"
         << endl;

    return 0;
}
