#pragma once
#include <cmath>

class zMAT4 {
    public:
        float matrix[4][4]; // 4x4-Matrix als Array


    // Zugriffsmethoden für bequeme Nutzung
    float* operator[](int row) {
        return matrix[row]; // Zugriff auf eine Zeile
    }

    const float* operator[](int row) const {
        return matrix[row];
    }

    void MakeRotationX(float angle) {
        float c = cos(angle);
        float s = sin(angle);

        // Setze Matrix auf Identität
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                matrix[i][j] = (i == j) ? 1.0f : 0.0f;

        // Anpassung für die Rotation
        matrix[1][1] = c;  // cos(angle)
        matrix[1][2] = -s; // -sin(angle)
        matrix[2][1] = s;  // sin(angle)
        matrix[2][2] = c;  // cos(angle)
    }

    void MakeRotationY(float angle) {
        float c = cos(angle);
        float s = sin(angle);

        // Setze Matrix auf Identität
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                matrix[i][j] = (i == j) ? 1.0f : 0.0f;

        // Anpassung für die Rotation um die Y-Achse
        matrix[0][0] = c;  // cos(angle)
        matrix[0][2] = s;  // sin(angle)
        matrix[2][0] = -s; // -sin(angle)
        matrix[2][2] = c;  // cos(angle)
    }

    void MakeRotationZ(float angle) {
        float c = cos(angle);
        float s = sin(angle);

        // Setze Matrix auf Identität
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                matrix[i][j] = (i == j) ? 1.0f : 0.0f;

        // Anpassung für die Rotation um die Z-Achse
        matrix[0][0] = c;  // cos(angle)
        matrix[0][1] = -s; // -sin(angle)
        matrix[1][0] = s;  // sin(angle)
        matrix[1][1] = c;  // cos(angle)
    }
    static void CalculateRotationMatrix(float yaw, float pitch, float roll, zMAT4& rotationMatrix) {
        float cosYaw = cos(yaw), sinYaw = sin(yaw);
        float cosPitch = cos(pitch), sinPitch = sin(pitch);
        float cosRoll = cos(roll), sinRoll = sin(roll);

        // Construct the rotation matrix
        rotationMatrix[0][0] = cosYaw * cosRoll - sinYaw * sinPitch * sinRoll;
        rotationMatrix[0][1] = -cosPitch * sinRoll;
        rotationMatrix[0][2] = sinYaw * cosRoll + cosYaw * sinPitch * sinRoll;
        rotationMatrix[0][3] = 0;

        rotationMatrix[1][0] = cosYaw * sinRoll + sinYaw * sinPitch * cosRoll;
        rotationMatrix[1][1] = cosPitch * cosRoll;
        rotationMatrix[1][2] = sinYaw * sinRoll - cosYaw * sinPitch * cosRoll;
        rotationMatrix[1][3] = 0;

        rotationMatrix[2][0] = -sinYaw * cosPitch;
        rotationMatrix[2][1] = sinPitch;
        rotationMatrix[2][2] = cosYaw * cosPitch;
        rotationMatrix[2][3] = 0;

        rotationMatrix[3][0] = 0;
        rotationMatrix[3][1] = 0;
        rotationMatrix[3][2] = 0;
        rotationMatrix[3][3] = 1;
    }
};