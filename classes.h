#include<iostream>
using namespace std;
class Mover;
class Pvector;
class Edge;
class Pvector {
private:
	double x, y;
public:
	friend class Mover;
	Pvector() { x = y = 0; };
	Pvector(double xx, double yy) :x(xx), y(yy) {};
	friend Pvector operator + (const Pvector & a, const Pvector & b) {
		return Pvector(a.x + b.x, a.y + b.y);
	};
	friend double operator*(const Pvector& a, const Pvector& b) {
		return a.x * b.x + a.y * b.y;
	};
	friend Pvector operator*(const Pvector& a, const double& b) {
		return Pvector(a.x * b, a.y * b);
	}
	friend Pvector operator*(const double& b, const Pvector& a) {
		return a * b;
	}
	friend Pvector operator/(const Pvector& a, const double& b) {
		return Pvector(a.x / b, a.y / b);
	}
	double magnitude() {
		return sqrt(x * x + y * y);
	}
	Pvector unix() {
		return (*this) / this->magnitude();
	}
};

class Edge {
private:
	double l, r, u, b;
public:
	friend class Mover;
	Edge() { l = r = u = b = 0; }
	Edge(double ll, double rr, double uu, double bb) :l(ll), r(rr), u(uu), b(bb) {};
};

class Mover {
private:
	Pvector location;
	Pvector velocity;
	Pvector acceleration;
	Edge bound;
	double vlimit;
public:
	Mover(Pvector ll = Pvector(), Pvector vv = Pvector(), Pvector acc = Pvector(), Edge bb = Edge(), double vl = 1.0)
		:location(ll), velocity(vv), acceleration(acc), bound(bb), vlimit(vl) {};
	Pvector getacc() {
		return acceleration;
	}
	int accelerate(Pvector acc) {
		acceleration = acceleration + acc;
		return 1;
	}
	int update() {
		velocity = velocity + acceleration;
		if (velocity.magnitude() > vlimit)
			velocity = velocity.unix() * vlimit;
		location = location + velocity;
		return 1;
	}
	int display() {
		// show the position
		return 1;
	}
	int checkpos() {
		if (location.x < bound.l) location.x = bound.l;
		if (location.x > bound.r) location.x = bound.r;
		if (location.y < bound.b) location.y = bound.b;
		if (location.y > bound.u) location.y = bound.u;
		return 1;
	}
};

class fly :private Mover {
public:
	int update() {
		Pvector acc(rand() % RAND_MAX, rand() % RAND_MAX); //fly flies randomly.
		accelerate(acc);
		Mover::update();
	}
};

class fish :private Mover {
public:
	int update() {
		Pvector origin_acc(Mover::getacc()), new_acc(rand() % RAND_MAX, rand() % RAND_MAX);
		while (origin_acc * new_acc < 0) {
			new_acc = Pvector(rand() % RAND_MAX, rand() % RAND_MAX);
		} // fish can't rotate more than 90°
		Mover::update();
	}
};

class bunny :private Mover {
public:
	int update() {
		Pvector acc(rand() % RAND_MAX, rand() % RAND_MAX); 
		accelerate(acc);
		Mover::update();
		accelerate(Pvector());// bunny jumps step by step, can't hold stable acceleration
	}
};
