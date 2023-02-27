def dfs(row, col, dest_row, dest_col, visited, path, flat_land):
    if (row, col) == (dest_row, dest_col):
        return True

    if flat_land[row][col] != ".." or (row, col) in visited:
        return False

    visited.add((row, col))
    path.append((row, col))

    for next_row, next_col in [(row-1, col), (row+1, col), (row, col-1), (row, col+1)]:
        if 0 <= next_row < len(flat_land) and 0 <= next_col < len(flat_land[0]):
            if dfs(next_row, next_col, dest_row, dest_col, visited, path, flat_land):
                return True

    path.pop()
    visited.remove((row, col))
    return False


def assign_parking_spaces(flat_land, events):
    parking_spaces = {}
    occupied_parking_spaces = set()

    for event in events:
        if event > 0:
            plane_num = event
            dest_row, dest_col = landing_locations[plane_num]
            for parking_space in parking_spaces.values():
                if parking_space == plane_num:
                    occupied_parking_spaces.add((parking_row, parking_col))

            for parking_row, parking_col in parking_locations[plane_num]:
                if (parking_row, parking_col) not in occupied_parking_spaces:
                    visited = set()
                    path = []
                    if dfs(dest_row, dest_col, parking_row, parking_col, visited, path, flat_land):
                        parking_spaces[(parking_row, parking_col)] = plane_num
                        occupied_parking_spaces.add((parking_row, parking_col))
                        break
            else:
                # Backtrack if no feasible path found
                for parking_row, parking_col in parking_locations[plane_num]:
                    if (parking_row, parking_col) in parking_spaces:
                        del parking_spaces[(parking_row, parking_col)]
                        occupied_parking_spaces.remove((parking_row, parking_col))
                return None

        else:
            plane_num = -event
            dest_row, dest_col = takeoff_locations
