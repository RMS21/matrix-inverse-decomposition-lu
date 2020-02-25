#include <iostream>

using namespace std;

const int N = 500;

double *mat[N];
double *lower[N], *upper[N], *inverse[N], *Z[N], *I[N];;

void lu()
{
    int i = 0, j = 0, k = 0;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (j < i)
                lower[j][i] = 0;
            else
            {
                lower[j][i] = mat[j][i];
                for (k = 0; k < i; k++)
                {
                    lower[j][i] = lower[j][i] - lower[j][k] * upper[k][i];
                }
            }
        }
        for (j = 0; j < N; j++)
        {
            if (j < i)
                upper[i][j] = 0;
            else if (j == i)
                upper[i][j] = 1;
            else
            {
                upper[i][j] = mat[i][j] / lower[i][i];
                for (k = 0; k < i; k++)
                {
                    upper[i][j] = upper[i][j] - ((lower[i][k] * upper[k][j]) / lower[i][i]);
                }
            }
        }
    }
}

void output(int *matrix[N])
{
    int i = 0, j = 0;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            cout << matrix[i][j] << '\t';
        }
        cout << endl;
    }
}


void output(float *matrix[N])
{
    int i = 0, j = 0;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            cout << matrix[i][j] << '\t';
        }
        cout << endl;
    }
}

void output(double *matrix[N])
{
    int i = 0, j = 0;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            cout << matrix[i][j] << '\t';
        }
        cout << endl;
    }
}

int compute_z(int col, int row) {
    int sum = 0;
    for(int i = 0; i < N; i++) {
        if(i != row) {
            sum += lower[row][i] * Z[i][col];
        }
    }

    int result = I[row][col] - sum;
    result = result / lower[row][row];

    return result;
}

int compute_inverse(int col, int row) {
    int sum = 0;
    for(int i = 0; i < N; i++) {
        if(i != row) {
            sum += upper[row][i] * inverse[i][col];
        }
    }

    int result = Z[row][col] - sum;
    result = result / upper[row][row];


    return result;
}


void inverse_matrix() {

    // compute z
    for(int col = 0; col < N; col++) {
        for(int row = 0; row < N; row++) {
            Z[row][col] = compute_z(col, row);
        }
    }
;
    // compute inverse
    for(int col = 0; col < N; col++) {
        for(int row = N - 1; row >= 0; row--) {
            inverse[row][col] = compute_inverse(col, row);
        }
    }
}

// Driver code
int main() {

    for (int i = 0; i < N; i++) {
        mat[i] = new double[N];
        lower[i] = new double[N];
        upper[i] = new double[N];
        inverse[i] = new double[N];
        Z[i] = new double[N];
        I[i] = new double[N];
    }

    cout << "Input matrix " << endl;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> mat[i][j];
            Z[i][j] = 0;
            if(i == j)
                I[i][j] = 1;
        }
    }

    lu();
    inverse_matrix();
    /*
    cout << "Matrix" << endl;
    output(mat);
    cout << endl << "Lower " << endl;
    output(lower);
    cout << endl <<  "Upper " << endl;
    output(upper);
    cout << endl <<  "Z " << endl;
    output(Z);
    */
    //cout << endl << "inverse " << endl;
    //output(inverse);

    return 0;
}
