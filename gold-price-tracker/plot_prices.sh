#!/bin/bash

# Advanced plotting script for cryptocurrency prices

# Set variables
DATA_FILE="gold_prices.csv"

# Check if data file exists
if [ ! -f "$DATA_FILE" ]; then
    echo "Error: Data file $DATA_FILE not found!"
    exit 1
fi

# Function 1: Basic price trend
plot_basic_trend() {
    gnuplot << EOF
    set terminal png size 800,600
    set output "plot1_basic_trend.png"
    set title "Cryptocurrency Price Trend"
    set xlabel "Time"
    set ylabel "Price (USD)"
    set xdata time
    set timefmt "%Y-%m-%d %H:%M:%S"
    set format x "%m/%d\n%H:%M"
    set xtics rotate
    set grid
    plot "$DATA_FILE" using 1:2 with linespoints title "Price" linecolor rgb "blue"
EOF
    echo "Created: plot1_basic_trend.png"
}

# Function 2: Price with points only
plot_points() {
    gnuplot << EOF
    set terminal png size 800,600
    set output "plot2_points.png"
    set title "Price Data Points"
    set xlabel "Time"
    set ylabel "Price (USD)"
    set xdata time
    set timefmt "%Y-%m-%d %H:%M:%S"
    set format x "%m/%d"
    set grid
    plot "$DATA_FILE" using 1:2 with points title "Price Points" pointtype 7 pointsize 2
EOF
    echo "Created: plot2_points.png"
}

# Function 3: Line chart only
plot_lines() {
    gnuplot << EOF
    set terminal png size 800,600
    set output "plot3_lines.png"
    set title "Price Line Chart"
    set xlabel "Time"
    set ylabel "Price (USD)"
    set xdata time
    set timefmt "%Y-%m-%d %H:%M:%S"
    set format x "%H:%M"
    set grid
    plot "$DATA_FILE" using 1:2 with lines title "Price Line" linewidth 2
EOF
    echo "Created: plot3_lines.png"
}

# Function 4: Bar chart
plot_bars() {
    gnuplot << EOF
    set terminal png size 800,600
    set output "plot4_bars.png"
    set title "Price Bar Chart"
    set xlabel "Time"
    set ylabel "Price (USD)"
    set style data histogram
    set style fill solid
    set grid
    plot "$DATA_FILE" using 2:xtic(1) with boxes title "Price Bars" linecolor rgb "green"
EOF
    echo "Created: plot4_bars.png"
}

# Function 5: Different color scheme
plot_red_theme() {
    gnuplot << EOF
    set terminal png size 800,600
    set output "plot5_red_theme.png"
    set title "Price Trend Red Theme"
    set xlabel "Time"
    set ylabel "Price (USD)"
    set xdata time
    set timefmt "%Y-%m-%d %H:%M:%S"
    set format x "%m/%d"
    set grid
    plot "$DATA_FILE" using 1:2 with linespoints title "Price" linecolor rgb "red" pointtype 5
EOF
    echo "Created: plot5_red_theme.png"
}

# Function 6: Area chart
plot_area() {
    gnuplot << EOF
    set terminal png size 800,600
    set output "plot6_area.png"
    set title "Price Area Chart"
    set xlabel "Time"
    set ylabel "Price (USD)"
    set xdata time
    set timefmt "%Y-%m-%d %H:%M:%S"
    set format x "%H:%M"
    set grid
    plot "$DATA_FILE" using 1:2 with filledcurves title "Price Area" linecolor rgb "orange"
EOF
    echo "Created: plot6_area.png"
}

# Function 7: Step chart
plot_steps() {
    gnuplot << EOF
    set terminal png size 800,600
    set output "plot7_steps.png"
    set title "Price Step Chart"
    set xlabel "Time"
    set ylabel "Price (USD)"
    set xdata time
    set timefmt "%Y-%m-%d %H:%M:%S"
    set format x "%m/%d"
    set grid
    plot "$DATA_FILE" using 1:2 with steps title "Price Steps" linecolor rgb "purple"
EOF
    echo "Created: plot7_steps.png"
}

# Function 8: Candlestick simplified
plot_candlestick() {
    gnuplot << EOF
    set terminal png size 800,600
    set output "plot8_candlestick.png"
    set title "Price Candlestick Simplified"
    set xlabel "Time"
    set ylabel "Price (USD)"
    set xdata time
    set timefmt "%Y-%m-%d %H:%M:%S"
    set format x "%H:%M"
    set grid
    plot "$DATA_FILE" using 1:2:2:2:2 with financebars title "Price Range" linecolor rgb "brown"
EOF
    echo "Created: plot8_candlestick.png"
}

# Function 9: Dot plot
plot_dots() {
    gnuplot << EOF
    set terminal png size 800,600
    set output "plot9_dots.png"
    set title "Price Dot Plot"
    set xlabel "Time"
    set ylabel "Price (USD)"
    set xdata time
    set timefmt "%Y-%m-%d %H:%M:%S"
    set format x "%m/%d"
    set grid
    plot "$DATA_FILE" using 1:2 with dots title "Price Dots" linecolor rgb "cyan"
EOF
    echo "Created: plot9_dots.png"
}

# Function 10: Impulses chart
plot_impulses() {
    gnuplot << EOF
    set terminal png size 800,600
    set output "plot10_impulses.png"
    set title "Price Impulses Chart"
    set xlabel "Time"
    set ylabel "Price (USD)"
    set xdata time
    set timefmt "%Y-%m-%d %H:%M:%S"
    set format x "%H:%M"
    set grid
    plot "$DATA_FILE" using 1:2 with impulses title "Price Impulses" linecolor rgb "magenta"
EOF
    echo "Created: plot10_impulses.png"
}

# Main execution
echo "Creating multiple plots..."
plot_basic_trend
plot_points
plot_lines
plot_bars
plot_red_theme
plot_area
plot_steps
plot_candlestick
plot_dots
plot_impulses

echo "All 10 plots created!"
ls -la plot*.png
