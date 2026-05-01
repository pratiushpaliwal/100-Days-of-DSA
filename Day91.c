// Day 91: Advanced Algorithms - Convex Hull
// Problem: Find Convex Hull using Graham Scan Algorithm

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 1005

struct Point {
    int x, y;
    int index;
} points[MAXN], hull[MAXN];

struct Point pivot;
int n, hull_size;

// Calculate squared distance between two points
long long dist_sq(struct Point a, struct Point b) {
    return (long long)(a.x - b.x) * (a.x - b.x) + (long long)(a.y - b.y) * (a.y - b.y);
}

// Cross product of vectors OA and OB
long long cross_product(struct Point O, struct Point A, struct Point B) {
    return (long long)(A.x - O.x) * (B.y - O.y) - (long long)(A.y - O.y) * (B.x - O.x);
}

// Check orientation of three points
// Returns: 0 -> collinear, 1 -> clockwise, 2 -> counterclockwise
int orientation(struct Point p, struct Point q, struct Point r) {
    long long val = cross_product(p, q, r);
    if (val == 0) return 0;
    return (val > 0) ? 2 : 1;
}

// Comparator for sorting points by polar angle with respect to pivot
int compare_polar(const void *a, const void *b) {
    struct Point *pa = (struct Point *)a;
    struct Point *pb = (struct Point *)b;
    
    int orient = orientation(pivot, *pa, *pb);
    
    if (orient == 0) {
        // If collinear, sort by distance from pivot
        long long dist_a = dist_sq(pivot, *pa);
        long long dist_b = dist_sq(pivot, *pb);
        return (dist_a < dist_b) ? -1 : 1;
    }
    
    return (orient == 2) ? -1 : 1;  // Counterclockwise comes first
}

// Find the bottom-most point (and leftmost in case of tie)
int find_bottom_point() {
    int min_y = points[0].y;
    int min_idx = 0;
    
    for (int i = 1; i < n; i++) {
        if (points[i].y < min_y || (points[i].y == min_y && points[i].x < points[min_idx].x)) {
            min_y = points[i].y;
            min_idx = i;
        }
    }
    
    return min_idx;
}

// Graham Scan algorithm to find convex hull
void graham_scan() {
    // Find the bottom-most point
    int bottom_idx = find_bottom_point();
    
    // Swap bottom point to first position
    struct Point temp = points[0];
    points[0] = points[bottom_idx];
    points[bottom_idx] = temp;
    
    pivot = points[0];
    
    // Sort points by polar angle with respect to pivot
    qsort(points + 1, n - 1, sizeof(struct Point), compare_polar);
    
    // Handle collinear points at the end
    int m = n - 1;
    while (m > 0 && orientation(pivot, points[n-1], points[m]) == 0) {
        m--;
    }
    
    // Reverse the order of collinear points at the end
    for (int i = m + 1, j = n - 1; i < j; i++, j--) {
        struct Point temp = points[i];
        points[i] = points[j];
        points[j] = temp;
    }
    
    // Create convex hull
    hull_size = 0;
    
    for (int i = 0; i < n; i++) {
        // Remove points that make clockwise turn
        while (hull_size > 1 && cross_product(hull[hull_size-2], hull[hull_size-1], points[i]) <= 0) {
            hull_size--;
        }
        
        hull[hull_size++] = points[i];
    }
}

// Calculate area of convex hull
double calculate_area() {
    if (hull_size < 3) return 0.0;
    
    double area = 0.0;
    for (int i = 0; i < hull_size; i++) {
        int j = (i + 1) % hull_size;
        area += (double)hull[i].x * hull[j].y - (double)hull[j].x * hull[i].y;
    }
    
    return fabs(area) / 2.0;
}

// Calculate perimeter of convex hull
double calculate_perimeter() {
    if (hull_size < 2) return 0.0;
    
    double perimeter = 0.0;
    for (int i = 0; i < hull_size; i++) {
        int j = (i + 1) % hull_size;
        double dx = hull[j].x - hull[i].x;
        double dy = hull[j].y - hull[i].y;
        perimeter += sqrt(dx * dx + dy * dy);
    }
    
    return perimeter;
}

// Check if a point is inside the convex hull
int point_in_hull(struct Point p) {
    if (hull_size < 3) return 0;
    
    for (int i = 0; i < hull_size; i++) {
        int j = (i + 1) % hull_size;
        if (cross_product(hull[i], hull[j], p) < 0) {
            return 0;  // Point is outside
        }
    }
    
    return 1;  // Point is inside or on boundary
}

void print_points() {
    printf("Points:\n");
    for (int i = 0; i < n; i++) {
        printf("Point %d: (%d, %d)\n", points[i].index, points[i].x, points[i].y);
    }
}

void print_hull() {
    printf("\nConvex Hull (in counterclockwise order):\n");
    for (int i = 0; i < hull_size; i++) {
        printf("Point %d: (%d, %d)\n", hull[i].index, hull[i].x, hull[i].y);
    }
    
    printf("\nHull properties:\n");
    printf("Number of vertices: %d\n", hull_size);
    printf("Area: %.2f\n", calculate_area());
    printf("Perimeter: %.2f\n", calculate_perimeter());
}

int main() {
    printf("Enter number of points: ");
    scanf("%d", &n);
    
    if (n < 3) {
        printf("Need at least 3 points for convex hull\n");
        return 1;
    }
    
    printf("Enter %d points (x y):\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
        points[i].index = i + 1;
    }
    
    print_points();
    
    // Find convex hull
    graham_scan();
    
    print_hull();
    
    // Test point inclusion
    printf("\nTest point inclusion (enter coordinates, -1 -1 to stop):\n");
    int test_x, test_y;
    while (scanf("%d %d", &test_x, &test_y) && (test_x != -1 || test_y != -1)) {
        struct Point test_point = {test_x, test_y, 0};
        if (point_in_hull(test_point)) {
            printf("Point (%d, %d) is inside or on the convex hull\n", test_x, test_y);
        } else {
            printf("Point (%d, %d) is outside the convex hull\n", test_x, test_y);
        }
    }
    
    return 0;
}