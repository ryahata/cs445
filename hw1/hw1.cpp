#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


/************************************
 * Functions
 ************************************/
template <typename Type>
void dprint(Type, bool);

void color_objects(int, int, int);

void foo(int, int, int);

void hacks();
int get_color(int, int);
void greedy_color(int, int, int);
void color(int, int, int);

void hacks_v2();

/************************************
 * Global vars
 ************************************/
vector< vector<int> > array;
int width, height;
int current_color = 1;
vector<int> color_map;

int main()
{
	fstream fin, fout;

	// Open the input file
	fin.open( "input.txt", fstream::in );

	// Open the output file
	fout.open( "output.txt", fstream::out );

	fin >> width;
	fin >> height;

	dprint(width, false);
	dprint(" ", false);
	dprint(height, true);

	// Read the array from the file and store the array properly
	for( int row = 0; row < height; row++ )
	{
		vector<int> temp;
		for( int col = 0; col < width; col++ )
		{
			int temp_int;
			fin >> temp_int;
			temp.push_back(temp_int);
		}
		array.push_back(temp);
	}

	// For debug print back the array to console
	for( int row = 0; row < height; row++ )
	{
		for( int col = 0; col < width; col++ )
		{
			dprint(array[row][col], false);
			dprint(" ", false);
		}
		dprint("", true);
	}

    hacks_v2();
    
    /*
	array[0][0] *= 2;
	if ( array[0][0] != 0 )
		current_color = 3;
	color_objects(0, 0, array[0][0]);
     */

	// Normalize
    /*
	for( int row = 0; row < height; row++ )
	{
		for( int col = 0; col < width; col++ )
		{
			if (array[row][col] > 0)
				array[row][col]--;
			else
				array[row][col] = 0;
		}
	}*/

	// For debug print back the array to console
	for( int row = 0; row < height; row++ )
	{
		for( int col = 0; col < width; col++ )
		{
			dprint(array[row][col], false);
			dprint(" ", false);
		}
		dprint("", true);
	}

	fout << width  << " " << height << endl;

	// For debug print back the array to console
	for( int row = 0; row < height; row++ )
	{
		for( int col = 0; col < width; col++ )
		{
			fout << array[row][col] << ' ';
		}
		fout << endl;
	}

	fin.close();
	fout.close();

	return 0;
}

void hacks_v2()
{
	for( int y = 0; y < height; y++ )
	{
		for( int x = 0; x < width; x++ )
		{
			if( array[y][x] == 1 )
			{
				vector<int> labels;
						
                // North
                if ( y > 0 && array[y - 1][x] != 0 )
                    labels.push_back(array[y - 1][x]);
                // West
                if ( x > 0 && array[y][x - 1] != 0 )
                    labels.push_back(array[y][x - 1]);
                // North West
                if ( y > 0 && x > 0 && array[y - 1][x - 1] != 0 )
                    labels.push_back(array[y - 1][x - 1]);
                // North east
                if ( y > 0 && x < width - 1 && array[y - 1][x + 1] != 0 )
                    labels.push_back(array[y - 1][x + 1]);
                // East
                //if ( x < width - 1 && array[y][x + 1] != 0 )
                //    labels.push_back(array[y][x + 1]);
                // South east
                //if ( y < height - 1 && x < width - 1 && array[y + 1][x + 1] != 0)
                //    labels.push_back(array[y + 1][x + 1]);
                // South
                //if ( y < height - 1 && array[y + 1][x] != 0 )
                //    labels.push_back(array[y + 1][x]);
                // South west
                //if ( y < height - 1 && x > 0 && array[y + 1][x - 1] != 0 )
                //    labels.push_back(array[y + 1][x - 1]);
                
                if (labels.size() != 0)
                {
                    int smallest = labels[0];
                    for( int i = 1; i < labels.size(); i++ )
                    {
                        if( smallest > labels[i] )
                            smallest = labels[i];
                    }
                    array[y][x] = smallest;
                    
                    for( int i = 0; i < labels.size(); i++ )
                    {
                        if( color_map.size() > labels[i] )
                            color_map[labels[i] - 1] = smallest; // EDIT added -1
                        else
                        {
                            //vector<int>::iterator itr = color_map.begin();
                            color_map.insert(color_map.begin() + labels[i] - 1, smallest);
                        }
                    }
                }
                else
                {
                    array[y][x] = current_color++;
                    //vector<int>::iterator itr = color_map.begin();
                    color_map.insert(color_map.begin() + array[y][x] - 1, array[y][x]);
                }
            }
		}
	}

	for( int row = 0; row < height; row++ )
	{
		for( int col = 0; col < width; col++ )
		{
            if (array[row][col] >= 1)
            {
                //array[row][col] = color_map[array[row][col] - 1]; // EDIT added -1
                int temp_color = color_map[array[row][col] - 1];
                while (temp_color > color_map[temp_color -1])
                {
                    temp_color = color_map[temp_color - 1];
                }
                array[row][col] = temp_color;
            }
		}
	}
}

void hacks()
{
    for( int row = 0; row < height; row++ )
	{
	for( int col = 0; col < width; col++ )
	{
            if ( array[row][col] == 1)
            {
                //array[row][col] = get_color(col, row);
                greedy_color(col, row, current_color++);
            }
        }
    }
}

// Try to color all 8 directions
void greedy_color(int col, int row, int color)
{
    // Do boundry checking
    if ( col < 0 || col > width || row < 0 || row > height )
        return;
    
    // If the value of the cell is one then color it
    if ( array[row][col] == 1 )
    {
        array[row][col] = color;
        
        // Try to color in all 8 directions
        greedy_color(col, row - 1, color);
        greedy_color(col, row + 1, color);
        greedy_color(col - 1, row, color);
        greedy_color(col - 1, row - 1, color);
        greedy_color(col - 1, row + 1, color);
        greedy_color(col + 1, row, color);
        greedy_color(col + 1, row - 1, color);
        greedy_color(col + 1, row + 1, color);
    }
    else
    {
        return;
    }
}

int get_color(int x, int y)
{
    // North
    if ( y > 0 && array[y - 1][x] > 1)
        return array[y - 1][x];
    // West
    else if ( x > 0 && array[y][x - 1] > 1 )
        return array[y][x - 1];
    // North West
    else if ( y > 0 && x > 0 && array[y - 1][x - 1] > 1 )
        return array[y - 1][x - 1];
    
    /*
    // North east
    else if ( y > 0 && x < width - 1 && array[y - 1][x + 1] > 1 )
        return array[y - 1][x + 1];
    // East
    else if ( x < width - 1 && array[y][x + 1] > 1 )
        return array[y][x + 1];
    // South east
    else if ( y < height - 1 && x < width - 1 && array[y + 1][x + 1] > 1 )
        return array[y + 1][x + 1];
    // South
    else if ( y < height - 1 && array[y + 1][x] > 1 )
        return array[y + 1][x];
    // South west
    else if ( y < height - 1 && x > 0 && array[y + 1][x - 1] > 1 )
        return array[y + 1][x - 1];
    */
    
    else
        return current_color++;
}

// This method will color the objects in the array recursively
// x - column number of the object
// y - row number of the object
// color - the color of the object before it that called the recursize function
void foo(int x, int y, int color)
{
    // Do boundry checking
    if ( x < 0 || x > width || y < 0 || y > height )
        return;

    // If the value is 1 then it hasn't been colored yet
    if ( array[y][x] == 1 )
    {
        // If the previous node that called the recursion did not have a color, assign it a new one
        if ( color == 0 )
        {
            array[y][x] *= current_color;
            
        }
            
    }
        
}

void color_objects(int x, int y, int color)
{
	// Check north
	if ( y > 0 )
	{
		if ( array[y - 1][x] == 1 )
		{
			// If the current color of the node is 0 then it is an empty space
			if ( color == 0 )
			{
				// Need to assign it the next new color
				array[y - 1][x] *= current_color;
                current_color++; // Shift the next new color
				color_objects(x, y - 1, array[y - 1][x]);
			}
			else
			{
				// Else use the current color
				array[y - 1][x] *= color;
				color_objects(x, y - 1, color);
			}
		}
		else if ( array[y - 1][x] == 0 )
		{
			array[y - 1][x] = -1;
			color_objects(x, y - 1, 0);
		}
		else
		{
			return;
		}
	}

	// Check north east
	if ( y > 0 && x < width - 1 )
	{
		if ( array[y - 1][x + 1] == 1 )
		{
			// If the current color of the node is 0 then it is an empty space
			if ( color == 0 )
			{
				// Need to assign it the next new color
				array[y - 1][x + 1] *= current_color;
                current_color++; // Shift the next new color
				color_objects(x + 1, y - 1, array[y - 1][x + 1]);
			}
			else
			{
				// Else use the current color
				array[y - 1][x + 1] *= color;
				color_objects(x + 1, y - 1, color);
			}
		}
		else if ( array[y - 1][x + 1] == 0 )
		{
			array[y - 1][x + 1] = -1;
			color_objects(x + 1, y - 1, 0);
		}
		else
		{
			return;
		}
	}

	// Check east
	if ( x < width - 1 )
	{
		if ( array[y][x + 1] == 1 )
		{
			// If the current color of the node is 0 then it is an empty space
			if ( color == 0 )
			{
				// Need to assign it the next new color
				array[y][x + 1] *= current_color;
                current_color++; // Shift the next new color
				color_objects(x + 1, y, array[y][x + 1]);
			}
			else
			{
				// Else use the current color
				array[y][x + 1] *= color;
				color_objects(x + 1, y, color);
			}
		}
		else if ( array[y][x + 1] == 0 )
		{
			array[y][x + 1] = -1;
			color_objects(x + 1, y, 0);
		}
		else 
		{
			return;
		}
	}

	// Check south east
	if ( y < height - 1 && x < width - 1)
	{
		if ( array[y + 1][x + 1] == 1 )
		{
			// If the current color of the node is 0 then it is an empty space
			if ( color == 0 )
			{
				// Need to assign it the next new color
				array[y + 1][x + 1] *= current_color;
                current_color++; // Shift the next new color
				color_objects(x + 1, y + 1, array[y + 1][x + 1]);
			}
			else
			{
				// Else use the current color
				array[y + 1][x + 1] *= color;
				color_objects(x + 1, y + 1, color);
			}
		}
		else if ( array[y + 1][x + 1] == 0 )
		{
			array[y + 1][x + 1] = -1;
			color_objects(x + 1, y + 1, 0);
		}
		else
		{
			return;
		}

	}

	// Check south
	if ( y <  height - 1 )
	{
		if ( array[y + 1][x] == 1 )
		{
			// If the current color of the node is 0 then it is an empty space
			if ( color == 0 )
			{
				// Need to assign it the next new color
				array[y + 1][x] *= current_color;
                current_color++; // Shift the next new color
				color_objects(x, y + 1, array[y + 1][x]);
			}
			else
			{
				// Else use the current color
				array[y + 1][x] *= color;
				color_objects(x, y + 1, color);
			}
		}
		else if ( array[y + 1][x] == 0 )
		{
			array[y + 1][x] = -1;
			color_objects(x, y + 1, 0);
		}
		else
		{
			return;
		}
	}

	// Check south west
	if ( y < height - 1 && x > 0)
	{
		if ( array[y + 1][x - 1] == 1 )
		{
			// If the current color of the node is 0 then it is an empty space
			if ( color == 0 )
			{
				// Need to assign it the next new color
				array[y + 1][x - 1] *= current_color;
                current_color++; // Shift the next new color
				color_objects(x - 1, y + 1, array[y + 1][x - 1]);
			}
			else
			{
				// Else use the current color
				array[y + 1][x - 1] *= color;
				color_objects(x - 1, y + 1, color);
			}
		}
		else if ( array[y + 1][x - 1] == 0 )
		{
			array[y + 1][x - 1] = -1;
			color_objects(x - 1, y + 1, 0);
		}
		else
		{
			return;
		}
	}

	// Check west
	if ( x > 0 )
	{
		if ( array[y][x - 1] == 1 )
		{
			// If the current color of the node is 0 then it is an empty space
			if ( color == 0 )
			{
				// Need to assign it the next new color
				array[y][x - 1] *= current_color;
                current_color++; // Shift the next new color
				color_objects(x - 1, y, array[y][x - 1]);
				
			}
			else
			{
				// Else use the current color
				array[y][x - 1] *= color;
				color_objects(x - 1, y, color);
			}
		}
		else if ( array[y][x - 1] == 0)
		{
			array[y][x - 1] = -1;
			color_objects(x - 1, y, 0);
		}
		else
		{ 
			return;
		}
	}

	// Check north west
	if ( y > 0 && x > 0 )
	{
		if ( array[y - 1][x - 1] == 1 )
		{
			// If the current color of the node is 0 then it is an empty space
			if ( color == 0 )
			{
				// Need to assign it the next new color
				array[y - 1][x - 1] *= current_color;
				current_color++; // Shift the next new color
                color_objects(x - 1, y - 1, array[y - 1][x - 1]);
			}
			else
			{
				// Else use the current color
				array[y - 1][x - 1] *= color;
				color_objects(x - 1, y - 1, color);
			}
		}
		else if ( array[y - 1][x - 1] == 0 )
		{
			array[y - 1][x - 1] = -1;
			color_objects(x - 1, y - 1, 0);
		}
		else
		{
			return;
		}
	}
}

// Debug print statement
// Will only print if tag RHYS_DEBUG is defined
// msg - the item you want to print to console
// include_break - include the line break if true
template <typename Type>
void dprint(Type msg, bool include_break)
{
#ifdef RHYS_DEBUG
	cout << msg;

	if(include_break)
		cout << endl;
#endif
}
