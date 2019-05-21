float getFPUreturnFPU(float fpu)
{
    fpu = fpu * 2;

    return fpu;
}

int main()
{
    float x = getFPUreturnFPU(2.0f);
}