#include <iostream>

// Fuzzy Logic functions
    double fuzzy_membership(double value, double start, double peak, double end) {
    if (value <= start || value >= end) return 0.0;
    if (value >= start && value <= peak) return (value - start) / (peak - start);
    if (value >= peak && value <= end) return (end - value) / (end - peak);
    return 0.0;
}

    double fuzzy_rule(double obstacle_distance, double bearing_angle) {
    // Define fuzzy sets for obstacle distance and bearing angle
    double near = fuzzy_membership(obstacle_distance, 0, 1, 2);
    double far = fuzzy_membership(obstacle_distance, 1, 3, 5);
    double small_angle = fuzzy_membership(bearing_angle, -30, 0, 30);
    double large_angle = fuzzy_membership(bearing_angle, 30, 0, 150);

    // Fuzzy rules (example rules, you need to define your own rules)
    double left_wheel_speed = near * small_angle;
    double right_wheel_speed = near * (-small_angle);

    // Combine rules (example combination, you may need more complex logic)
    double left_velocity = left_wheel_speed + 0.5 * far * large_angle;
    double right_velocity = right_wheel_speed + 0.5 * far * (-large_angle);

    // Limit the velocities to a reasonable range
    if (left_velocity > 1.0) left_velocity = 1.0;
    if (left_velocity < -1.0) left_velocity = -1.0;
    if (right_velocity > 1.0) right_velocity = 1.0;
    if (right_velocity < -1.0) right_velocity = -1.0;

    // Output velocities
    std::cout << "Left Wheel Velocity: " << left_velocity << std::endl;
    std::cout << "Right Wheel Velocity: " << right_velocity << std::endl;

    return 0;
}

int main() {
    double obstacle_distance; // Distance to the obstacle (input)
    double bearing_angle; // Bearing angle to the obstacle (input)

    std::cout << "Enter obstacle distance (in meters): ";
    std::cin >> obstacle_distance;

    std::cout << "Enter bearing angle (in degrees): ";
    std::cin >> bearing_angle;

    fuzzy_rule(obstacle_distance, bearing_angle);

    return 0;
}