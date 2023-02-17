#include <kalmanfilter.h>

#define XQVAL 0.0125 // 1.375
#define XRVAL 0.0125 // 2.236

#define YQVAL 0.0125 // 1.375
#define YRVAL 0.0125 // 2.236

#define WQVAL 0.01 // 0.125
#define WRVAL 0.01 // 0.125

#define XVAR 0.01 // 0.225
#define YVAR 0.01 // 0.225

#define SAMPLE_SIZE 50

KalmanFilter::KalmanFilter() : 
    T(1)
{
    x(0) = 0;
    x(1) = 0;
    x(2) = 0;

    H.setIdentity();
    P.setIdentity();
    P_.setIdentity();
    first_update = true;
    
    Q << XQVAL * XQVAL, XQVAL * XQVAL / 100.0, XQVAL * XQVAL / 100.0,
        YQVAL * YQVAL / 100.0, YQVAL * YQVAL, YQVAL * YQVAL / 100.0,
        WQVAL * WQVAL / 100.0, WQVAL * WQVAL / 100.0, WQVAL * WQVAL;

    R << XRVAL * XRVAL, XRVAL * XRVAL / 100.0, XRVAL * XRVAL / 100.0,
        YRVAL * YRVAL / 100.0, YRVAL * YRVAL, YRVAL * YRVAL / 100.0,
        WRVAL * WRVAL / 100.0, WRVAL * WRVAL / 100.0, WRVAL * WRVAL;

    std::cout << "[KalmanFilter] matrix R :\n"
              << R << std::endl;
    std::cout << "[KalmanFilter] matrix Q :\n"
              << Q << std::endl;
}

KalmanFilter::~KalmanFilter()
{
}

void KalmanFilter::estimate()
{
    double psi = x(2);
    B << T * cos(psi), -T * sin(psi), 0,
        T * sin(psi), T * cos(psi), 0,
        0, 0, T;

    // std::cout << "Psi : " << psi << "B:\n" << B << std::endl;

    x_ = x + B * u;
    A.setIdentity();
    P_ = A * P * A.transpose() + Q;
}

void KalmanFilter::measure()
{
    K = P_ * H.transpose() * (H * P_ * H.transpose() + R).inverse();
    x = x_ + K * (z - H * x_);
    P = (Eigen::Matrix3d::Identity() - K * H) * P_;
}

void measure();

void KalmanFilter::setX(double x)
{
    this->x(0) = x;
}

void KalmanFilter::setY(double y)
{
    this->x(1) = y;
}

void KalmanFilter::setT(double t)
{
    this->T = t;
}

void KalmanFilter::setState(double x1, double x2, double x3)
{
    x(0) = x1;
    x(1) = x2;
    x(2) = x3;
}
void KalmanFilter::setControl(double u1, double u2, double u3)
{
    u(0) = u1;
    u(1) = u2;
    u(2) = u3;
}

void KalmanFilter::setMeasurement(double z1, double z2, double z3)
{
    z(0) = z1;
    z(1) = z2;
    z(2) = z3;
}

void KalmanFilter::update(double T, double u1, double u2, double u3, double z1, double z2, double z3)
{
    if (first_update)
    {
        setState(z1, z2, z3);
        // setControl(0,0,z3);
        first_update = false;
    }
    else
    {
        printf("[update filter] T:%f u1:%f u2:%f u3:%f z1:%f z2:%f z3:%f\n",T,u1,u2,u3,z1,z2,z3);
        setT(T);
        setControl(u1, u2, u3);
        setMeasurement(z1, z2, z3);
        estimate();
        measure();
        //        std::cout << "X:" << x << std::endl;
    }

#ifdef MOTION_UNCERTAINITY

    std::random_device xrd, yrd;
    std::normal_distribution<> xgen(0.0, XVAR), ygen(0.0, YVAR);
    // std::uniform_real_distribution<> xgen(-XVAR,XVAR), ygen(-YVAR,YVAR);

    double randx = 0.0;
    double randy = 0.0;

    for (int i = 0; i < SAMPLE_SIZE; i++)
    {

        // randx += xgen(xrd);
        // randy += ygen(yrd);

        auto tempx = xgen(xrd);
        auto tempy = ygen(yrd);

        randx = std::max(randx, std::fabs(tempx));
        randy = std::max(randy, std::fabs(tempy));

        randx = randx == std::fabs(tempx) ? tempx : randx;
        randy = randy == std::fabs(tempy) ? tempy : randy;
    }

    // randx /= SAMPLE_SIZE;
    // randy /= SAMPLE_SIZE;

    x(0) += randx * u1;
    x(1) += randy * u2;

#endif

    X = x(0);
    Y = x(1);
    Theta = x(2);
}

double KalmanFilter::getTheta()
{
    return this->Theta;
}

double KalmanFilter::getX()
{
    return this->X;
}

double KalmanFilter::getY()
{
    return this->Y;
}

double KalmanFilter::getVx()
{
    return u(0);
}

double KalmanFilter::getVy()
{
    return u(1);
}