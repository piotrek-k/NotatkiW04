double getDoubleReturnDouble(double a, double b, double c)
{
    double fpu = a / b;
    fpu *= 2 * c;

    return fpu;
}

int main()
{
    double x = getDoubleReturnDouble(2.0f, 3.0f, 5.0);
}