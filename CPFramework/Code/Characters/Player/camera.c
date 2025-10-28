#include "cprocessing.h"
#include "utils.h"

void MoveCamera(int x, int y, void *func(void)) {
    CP_Settings_ResetMatrix();

    // The position of the rectangle we are drawing
    CP_Vector position = CP_Vector_Set(x, y);

    // Create a transform matrix
    CP_Matrix scale = CP_Matrix_Scale(CP_Vector_Set(1, 1));
    CP_Matrix translate = CP_Matrix_Translate(position);
    CP_Matrix rotate = CP_Matrix_Rotate(0.0f);

    // Combine transform (translate * rotation * scale)
    CP_Matrix transform = CP_Matrix_Multiply(translate, CP_Matrix_Multiply(rotate, scale));

    // Set the camera transform to the created matrix
    CP_Settings_ApplyMatrix(transform);

    func();

    // Reset the transform matrix to the identity matrix
    CP_Settings_ResetMatrix();
}