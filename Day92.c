// Day 92: Advanced Algorithms - Line Sweep
// Problem: Rectangle Union Area using Line Sweep Algorithm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1005

struct Rectangle {
    int x1, y1, x2, y2;
} rectangles[MAXN];

struct Event {
    int x, y1, y2, type;  // type: 1 for start, -1 for end
} events[MAXN * 2];

struct Segment {
    int y1, y2, count;
} segments[MAXN * 4];

int n, event_count;
int y_coords[MAXN * 2], y_count;

// Comparator for events (sort by x-coordinate)
int compare_events(const void *a, const void *b) {
    struct Event *ea = (struct Event *)a;
    struct Event *eb = (struct Event *)b;
    
    if (ea->x != eb->x) return ea->x - eb->x;
    return eb->type - ea->type;  // Process end events before start events
}

// Comparator for y-coordinates
int compare_int(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

// Compress y-coordinates
void compress_coordinates() {
    y_count = 0;
    
    for (int i = 0; i < n; i++) {
        y_coords[y_count++] = rectangles[i].y1;
        y_coords[y_count++] = rectangles[i].y2;
    }
    
    qsort(y_coords, y_count, sizeof(int), compare_int);
    
    // Remove duplicates
    int unique_count = 1;
    for (int i = 1; i < y_count; i++) {
        if (y_coords[i] != y_coords[unique_count - 1]) {
            y_coords[unique_count++] = y_coords[i];
        }
    }
    y_count = unique_count;
}

// Find compressed coordinate
int find_coord(int y) {
    int left = 0, right = y_count - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (y_coords[mid] == y) return mid;
        if (y_coords[mid] < y) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// Update segment tree for range [y1, y2]
void update_segments(int y1, int y2, int delta) {
    int start = find_coord(y1);
    int end = find_coord(y2);
    
    for (int i = start; i < end; i++) {
        segments[i].count += delta;
    }
}

// Calculate total length of covered segments
long long calculate_covered_length() {
    long long total = 0;
    
    for (int i = 0; i < y_count - 1; i++) {
        if (segments[i].count > 0) {
            total += y_coords[i + 1] - y_coords[i];
        }
    }
    
    return total;
}

// Line sweep algorithm to find union area
long long rectangle_union_area() {
    // Create events
    event_count = 0;
    for (int i = 0; i < n; i++) {
        events[event_count++] = (struct Event){rectangles[i].x1, rectangles[i].y1, rectangles[i].y2, 1};
        events[event_count++] = (struct Event){rectangles[i].x2, rectangles[i].y1, rectangles[i].y2, -1};
    }
    
    // Sort events by x-coordinate
    qsort(events, event_count, sizeof(struct Event), compare_events);
    
    // Compress y-coordinates
    compress_coordinates();
    
    // Initialize segments
    for (int i = 0; i < y_count - 1; i++) {
        segments[i] = (struct Segment){y_coords[i], y_coords[i + 1], 0};
    }
    
    long long total_area = 0;
    int prev_x = events[0].x;
    
    for (int i = 0; i < event_count; i++) {
        // Add area from previous x to current x
        if (i > 0 && events[i].x != prev_x) {
            long long width = events[i].x - prev_x;
            long long height = calculate_covered_length();
            total_area += width * height;
            prev_x = events[i].x;
        }
        
        // Update segments based on current event
        update_segments(events[i].y1, events[i].y2, events[i].type);
    }
    
    return total_area;
}

// Alternative problem: Count intersections using line sweep
struct Point {
    int x, y, id;
} points[MAXN];

struct LineSegment {
    int x1, y1, x2, y2, id;
} lines[MAXN];

int point_count, line_count;

// Check if point lies on line segment
int point_on_segment(struct Point p, struct LineSegment seg) {
    // Check if point is on the line (assuming horizontal/vertical segments)
    if (seg.y1 == seg.y2) {  // Horizontal segment
        return (p.y == seg.y1 && p.x >= seg.x1 && p.x <= seg.x2);
    } else if (seg.x1 == seg.x2) {  // Vertical segment
        return (p.x == seg.x1 && p.y >= seg.y1 && p.y <= seg.y2);
    }
    return 0;
}

void count_intersections() {
    printf("\nCounting point-segment intersections:\n");
    
    for (int i = 0; i < point_count; i++) {
        int intersection_count = 0;
        printf("Point %d (%d, %d) intersects with segments: ", 
               points[i].id, points[i].x, points[i].y);
        
        for (int j = 0; j < line_count; j++) {
            if (point_on_segment(points[i], lines[j])) {
                printf("%d ", lines[j].id);
                intersection_count++;
            }
        }
        
        if (intersection_count == 0) {
            printf("none");
        }
        printf(" (total: %d)\n", intersection_count);
    }
}

int main() {
    printf("Choose problem:\n");
    printf("1. Rectangle Union Area\n");
    printf("2. Point-Segment Intersections\n");
    
    int choice;
    scanf("%d", &choice);
    
    if (choice == 1) {
        printf("Enter number of rectangles: ");
        scanf("%d", &n);
        
        printf("Enter %d rectangles (x1 y1 x2 y2):\n", n);
        for (int i = 0; i < n; i++) {
            scanf("%d %d %d %d", &rectangles[i].x1, &rectangles[i].y1, 
                  &rectangles[i].x2, &rectangles[i].y2);
            
            // Ensure x1 <= x2 and y1 <= y2
            if (rectangles[i].x1 > rectangles[i].x2) {
                int temp = rectangles[i].x1;
                rectangles[i].x1 = rectangles[i].x2;
                rectangles[i].x2 = temp;
            }
            if (rectangles[i].y1 > rectangles[i].y2) {
                int temp = rectangles[i].y1;
                rectangles[i].y1 = rectangles[i].y2;
                rectangles[i].y2 = temp;
            }
        }
        
        long long area = rectangle_union_area();
        printf("\nTotal union area: %lld\n", area);
        
    } else {
        printf("Enter number of points: ");
        scanf("%d", &point_count);
        
        printf("Enter %d points (x y):\n", point_count);
        for (int i = 0; i < point_count; i++) {
            scanf("%d %d", &points[i].x, &points[i].y);
            points[i].id = i + 1;
        }
        
        printf("Enter number of line segments: ");
        scanf("%d", &line_count);
        
        printf("Enter %d line segments (x1 y1 x2 y2):\n", line_count);
        for (int i = 0; i < line_count; i++) {
            scanf("%d %d %d %d", &lines[i].x1, &lines[i].y1, 
                  &lines[i].x2, &lines[i].y2);
            lines[i].id = i + 1;
            
            // Ensure proper ordering
            if (lines[i].x1 > lines[i].x2 || 
                (lines[i].x1 == lines[i].x2 && lines[i].y1 > lines[i].y2)) {
                int temp;
                temp = lines[i].x1; lines[i].x1 = lines[i].x2; lines[i].x2 = temp;
                temp = lines[i].y1; lines[i].y1 = lines[i].y2; lines[i].y2 = temp;
            }
        }
        
        count_intersections();
    }
    
    return 0;
}