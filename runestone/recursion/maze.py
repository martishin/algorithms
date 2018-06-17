#!/usr/bin/env python

def searchFrom(maze, start_row, start_column):
    maze.updatePosition(start_row, start_column)
    if maze[start_row][start_column] == OBSTACLE:
        return False
    if maze[start_row][start_column] == TRIED:
        return False
    if maze.isExit(start_row, start_column):
        maze.updatePosition(start_row, start_column, PART_OF_PATH)
        return True
    maze.updatePosition(start_row, start_column, TRIED)

    found = searchFrom(maze, start_row - 1, start_column) or \
            searchFrom(maze, start_row + 1, start_column) or \
            searchFrom(maze, start_row, start_column - 1) or \
            searchFrom(maze, start_row, start_column + 1)
    if found:
        maze.updatePosition(start_row, start_column, PART_OF_PATH)
    else:
        maza.updatePosition(start_row, start_column, DEAD_END)
    return found
