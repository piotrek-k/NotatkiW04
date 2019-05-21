float getFPUreturnFPU(float a, float b)
{
    float fpu = a / b;

    return fpu;
}

int main()
{
    float x = getFPUreturnFPU(2.0f, 3.0f);
}