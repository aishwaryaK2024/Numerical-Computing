#include "Matrix.hpp"

int main()
{
    try {
        Matrix left("225left.txt");
        Matrix right("225right.txt");

        Matrix augmented = left.createAugmented(right);

        GEWithPivot solver(augmented);  

        solver.gaussianElimination();

        std::vector<double> solution = solver.backSubstitution();

        std::ofstream out("result225.txt");
        for (double val : solution)
            out << val << std::endl;

        out.close();

        std::cout << "Solution written\n";
    }
    catch (std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}