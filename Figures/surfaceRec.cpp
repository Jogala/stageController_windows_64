#include "figures.h"

//surfaceRectangle																									
void figures::surfaceRectangle::set(double aIn, double bIn, double phi0In, double velocityIn, int resolutionIn, char longOrShortSide){


	velocity = velocityIn;
	a = aIn;
	b = bIn;
	phi0 = phi0In*(2 * pi) / (360.0);
	resolution = resolutionIn;
	orientation = longOrShortSide;

}
void figures::surfaceRectangle::cutRel()
{
	::gE545.setVelocity(velocity, velocity, 10);
	double delta = b / resolution;

	double pos[3];
	::gE545.getPositon(pos);

	double deltaPhi[2];
	double R;
	double x0, y0;
	double h = 3;

	R = 0.5*sqrt(a*a + b*b);
	deltaPhi[0] = 2 * atan(b / a);
	deltaPhi[1] = 2 * atan(a / b);

	double phiStart = phi0 - deltaPhi[0] / 2.0;

	x0 = R*cos(phiStart);
	y0 = R*sin(phiStart);


	double deltaX = a*cos(phi0);
	double deltaY = b*sin(phi0);

	double kDeltaX = -cos(phi0)*h - sin(phi0)*delta / 2;
	double kDeltaY = -sin(phi0)*h + cos(phi0)*delta / 2;

	double zkDeltaX = cos(phi0)*h - sin(phi0)*delta / 2;
	double zkDeltaY = sin(phi0)*h + cos(phi0)*delta / 2;

	::gE545.move(x0, y0, 0);

	for (int i = 0; i <= (resolution - 1); i++){
		::gE545.openShutter();
		::gE545.move(-deltaX, -deltaY, 0);
		::gE545.closeShutter();
		::gE545.move(kDeltaX, kDeltaY, 0);
		::gE545.move(zkDeltaX, zkDeltaX, 0);
		::gE545.openShutter();
		::gE545.move(deltaX, deltaY, 0);
		::gE545.closeShutter();
		::gE545.move(zkDeltaX, zkDeltaX, 0);
		::gE545.move(kDeltaX, kDeltaY, 0);
	}
	::gE545.openShutter();
	::gE545.move(-deltaX, -deltaY, 0);

	::gE545.closeShutter();

	::gE545.moveTo(pos);
}
void figures::surfaceRectangle::cutAbs()
{
	::gE545.setVelocity(velocity, velocity, 10);
	double delta = b / resolution;
	double pos[3];
	double deltaPhi[2];
	double R;
	double x0, y0;
	double h = 3;

	::gE545.getPositon(pos);

	R = 0.5*sqrt(a*a + b*b);
	deltaPhi[0] = 2 * atan(b / a);
	deltaPhi[1] = 2 * atan(a / b);

	double phiStart = phi0 - deltaPhi[0] / 2.0;

	x0 = R*cos(phiStart);
	y0 = R*sin(phiStart);

	double deltaX = a*cos(phi0);
	double deltaY = b*sin(phi0);

	double kDeltaX = -cos(phi0)*h - sin(phi0)*delta / 2;
	double kDeltaY = -sin(phi0)*h + cos(phi0)*delta / 2;

	double zkDeltaX = cos(phi0)*h - sin(phi0)*delta / 2;
	double zkDeltaY = sin(phi0)*h + cos(phi0)*delta / 2;

	::gE545.moveTo(x0 + pos[0], y0 + pos[1], pos[2]);

	for (int i = 0; i <= (resolution - 1); i++){
		::gE545.openShutter();
		::gE545.moveTo(-deltaX + pos[0], -deltaY + pos[1], +pos[2]);
		::gE545.closeShutter();
		::gE545.moveTo(kDeltaX + pos[0], kDeltaY + pos[1], pos[2]);
		::gE545.moveTo(zkDeltaX + pos[0], zkDeltaX + pos[1], pos[2]);
		::gE545.openShutter();
		::gE545.moveTo(deltaX + pos[0], deltaY + pos[1], pos[2]);
		::gE545.closeShutter();
		::gE545.moveTo(zkDeltaX + pos[0], zkDeltaX + pos[1], pos[2]);
		::gE545.moveTo(kDeltaX + pos[0], kDeltaY + pos[1], pos[2]);
	}
	::gE545.openShutter();
	::gE545.moveTo(-deltaX + pos[0], -deltaY + pos[1], pos[2]);

	::gE545.closeShutter();
	::gE545.moveTo(pos);

}
