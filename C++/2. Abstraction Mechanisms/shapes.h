// ======================================================================
// shapes.h
// 
// Demonstrates:
// - Abstract base class (Shape) with pure virtual functions
// - Virtual destructor
// - Derived classes: Circle, Rectangle, Triangle
// - Polymorphic usage through base pointers
// - Clone pattern (virtual clone())
// - dynamic_cast and typeid
// ======================================================================

#ifndef SHAPES_H
#define SHAPES_H

#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <memory>

// Abstract base class
class Shape {
public:
    virtual ~Shape() = default;                 // virtual destructor

    virtual double area() const = 0;            // pure virtual
    virtual void draw(std::ostream& os) const = 0;  // draw to a stream
    virtual std::unique_ptr<Shape> clone() const = 0; // clone pattern

    // Non-virtual helper to print to stdout
    void print() const { draw(std::cout); std::cout << " (area=" << area() << ")\n"; }
};

class Circle : public Shape {
public:
    Circle(double r) : radius_(r) {}
    double area() const override { return M_PI * radius_ * radius_; }
    void draw(std::ostream& os) const override {
        os << "Circle(radius=" << radius_ << ")";
    }
    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Circle>(*this);
    }
    double radius() const { return radius_; }
private:
    double radius_;
};

class Rectangle : public Shape {
public:
    Rectangle(double w, double h) : width_(w), height_(h) {}
    double area() const override { return width_ * height_; }
    void draw(std::ostream& os) const override {
        os << "Rectangle(width=" << width_ << ", height=" << height_ << ")";
    }
    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Rectangle>(*this);
    }
private:
    double width_, height_;
};

class Triangle : public Shape {
public:
    Triangle(double base, double height) : base_(base), height_(height) {}
    double area() const override { return 0.5 * base_ * height_; }
    void draw(std::ostream& os) const override {
        os << "Triangle(base=" << base_ << ", height=" << height_ << ")";
    }
    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Triangle>(*this);
    }
private:
    double base_, height_;
};

// Free function: total area of a vector of Shapes (polymorphic)
double totalArea(const std::vector<std::unique_ptr<Shape>>& shapes);

// Draw all shapes
void drawAll(const std::vector<std::unique_ptr<Shape>>& shapes, std::ostream& os);

#endif // SHAPES_H