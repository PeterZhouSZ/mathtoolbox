#include <iostream>
#include <Eigen/Core>
#include <mathtoolbox/bfgs.hpp>
#include <optimization-test-functions.hpp>

int main()
{
    constexpr otf::FunctionType type = otf::FunctionType::Sphere;
    constexpr int dimensions = 3;

    mathtoolbox::Setting setting;
    setting.x_init = Eigen::VectorXd::Random(dimensions);
    setting.f = [](const Eigen::VectorXd& x) { return otf::GetValue(x, type); };
    setting.g = [](const Eigen::VectorXd& x) { return otf::GetGrad(x, type); };
    setting.type = mathtoolbox::Type::Min;

    const mathtoolbox::Result result = mathtoolbox::RunOptimization(setting);

    const Eigen::VectorXd expected_solution = otf::GetSolution(dimensions, type);

    std::cout << "#iterations: " << result.num_iterations << std::endl;
    std::cout << "Found solution: " << result.x_star.transpose() << " (" << result.y_star << ")" << std::endl;
    std::cout << "Expected solution: " << expected_solution.transpose() << " (" << otf::GetValue(expected_solution, type) << ")" << std::endl;

    return 0;
}
