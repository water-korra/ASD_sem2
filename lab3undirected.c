#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define n 12
#define n1n2n3n4 0423

double **randm(int rows, int cols)
{
    double **matrix = (double **)malloc(rows * sizeof(double *));

    for (int i = 0; i < rows; i++)
        matrix[i] = (double *)malloc(cols * sizeof(double));

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            double temp = rand() % 21;
            matrix[i][j] = temp / 10;
        }
    }

    return matrix;
}

double **mirrorMatrix(double **matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix[i][j] == 1)
            {
                matrix[j][i] = 1;
            }
        }
    }

    return matrix;
}

double **mulmr(double coef, double **matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] = matrix[i][j] * coef;

            if (matrix[i][j] < 1.0)
            {
                matrix[i][j] = 0;
            }
            else
                matrix[i][j] = 1;
        }
    }

    return matrix;
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
char ProgName[] = "lab3";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG lpMsg;

    WNDCLASS w;

    w.lpszClassName = ProgName;
    w.hInstance = hInstance;
    w.lpfnWndProc = WndProc;
    w.hCursor = LoadCursor(NULL, IDC_ARROW);
    w.hIcon = 0;
    w.lpszMenuName = 0;
    w.hbrBackground = LTGRAY_BRUSH;
    w.style = CS_HREDRAW | CS_VREDRAW;
    w.cbWndExtra = 0;

    if (!RegisterClass(&w))
        return 0;

    hWnd = CreateWindow(ProgName,
                        "lab3 sedush mykhaylo",
                        WS_OVERLAPPEDWINDOW,
                        800,
                        100,
                        1000,
                        900,
                        (HWND)NULL,
                        (HMENU)NULL,
                        (HINSTANCE)hInstance,
                        (HINSTANCE)NULL);

    ShowWindow(hWnd, nCmdShow);

    while (GetMessage(&lpMsg, hWnd, 0, 0))
    {
        TranslateMessage(&lpMsg);
        DispatchMessage(&lpMsg);
    }
    return (lpMsg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT messg,
                         WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;

    void arrow(float fi, int px, int py)
    {
        fi = 3.1416 * (180.0 - fi) / 180.0;
        int lx, ly, rx, ry;

        lx = px + 15 * cos(fi + 0.3);
        rx = px + 15 * cos(fi - 0.3);
        ly = py + 15 * sin(fi + 0.3);
        ry = py + 15 * sin(fi - 0.3);
        MoveToEx(hdc, lx, ly, NULL);
        LineTo(hdc, px, py);
        LineTo(hdc, rx, ry);
    }

    switch (messg)
    {

    case WM_PAINT:

        hdc = BeginPaint(hWnd, &ps);

        char *nn[n] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"};
        int nx[n] = {};
        int ny[n] = {};
        int num = 200;
        for (int i = 0; i < n; i++)
        {
            if (i == 0)
            {
                nx[i] = num;
                ny[i] = num;
            }
            else if (i < 4)
            {
                nx[i] = nx[i - 1] + num;
                ny[i] = ny[i - 1];
            }
            else if (i < 7)
            {
                nx[i] = nx[i - 1];
                ny[i] = ny[i - 1] + num;
            }
            else if (i < 10)
            {
                nx[i] = nx[i - 1] - num;
                ny[i] = ny[i - 1];
            }
            else
            {
                nx[i] = nx[i - 1];
                ny[i] = ny[i - 1] - num;
            }
        }
        int dx = 20, dy = 20, dtx = 5;
        int i;

        HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
        HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

        srand(n1n2n3n4);
        double **T = randm(n, n);
        double coefficient = 1.0 - 1 * 0.02 - 3 * 0.005 - 0.25;
        double **A_temp = mulmr(coefficient, T, n, n);
        double **A = mirrorMatrix(A_temp, n, n);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                printf("%g ", A[i][j]);
            }
            printf("\n");
        }

        SelectObject(hdc, KPen);

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (A[i][j] == 1)
                {
                    MoveToEx(hdc, nx[i], ny[i], NULL);

                    if ((ny[i] == ny[j]) && (nx[j] != nx[i] + num) && (nx[j] != nx[i] - num))
                    {

                        if (i < 4)
                        {
                            if (nx[i] < nx[j])
                            {
                                Arc(hdc, nx[i], ny[i] - 50, nx[j], ny[j] + 50, nx[j], ny[j], nx[i], ny[i]);
                            }
                            else if (nx[i] > nx[j])
                            {
                                Arc(hdc, nx[j], ny[j] - 40, nx[i], ny[i] + 40, nx[i], ny[i], nx[j], ny[j]);
                            }
                        }
                        else if (i > 5 && i < 10)
                        {
                            if (nx[i] < nx[j])
                            {
                                Arc(hdc, nx[j], ny[j] - 50, nx[i], ny[i] + 50, nx[i], ny[i], nx[j], ny[j]);
                            }
                            else if (nx[i] > nx[j])
                            {
                                Arc(hdc, nx[i], ny[i] - 40, nx[j], ny[j] + 40, nx[j], ny[j], nx[i], ny[i]);
                            }
                        }
                    }
                    else if (((nx[i] == nx[j]) && (ny[j] != ny[i] + num) && (ny[j] != ny[i] - num) && (nx[i] == num || nx[i] == num * 4)) &&
                             ((nx[i] == nx[j]) && (ny[j] != ny[i] + num * 1.5) && (ny[j] != ny[i] - num * 1.5)))
                    {

                        if (i > 2 && i < 7)
                        {
                            if (ny[i] < ny[j])
                            {
                                Arc(hdc, nx[i] - 40, ny[i], nx[j] + 40, ny[j], nx[j], ny[j], nx[i], ny[i]);
                            }
                            else if (ny[i] > ny[j])
                            {
                                Arc(hdc, nx[j] - 50, ny[j], nx[i] + 50, ny[i], nx[i], ny[i], nx[j], ny[j]);
                            }
                        }
                        else if (i > 8)
                        {
                            if (ny[i] < ny[j])
                            {
                                Arc(hdc, nx[j] - 40, ny[j], nx[i] + 40, ny[i], nx[i], ny[i], nx[j], ny[j]);
                            }
                            else if (ny[i] > ny[j])
                            {
                                Arc(hdc, nx[i] - 40, ny[i], nx[j] + 40, ny[j], nx[j], ny[j], nx[i], ny[i]);
                            }
                        }
                    }
                    else
                    {
                        LineTo(hdc, nx[j], ny[j]);
                    }
                }
            }
        }

        SelectObject(hdc, BPen);
        for (i = 0; i < n; i++)
        {
            Ellipse(hdc, nx[i] - dx, ny[i] - dy, nx[i] + dx, ny[i] + dy);
            if (i < 9)
            {
                TextOut(hdc, nx[i] - dtx, ny[i] - dy / 2, nn[i], 1);
            }
            else
                TextOut(hdc, nx[i] - dtx, ny[i] - dy / 1.5, nn[i], 2);
        }

        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return (DefWindowProc(hWnd, messg, wParam, lParam));
    }
    return 0;
}