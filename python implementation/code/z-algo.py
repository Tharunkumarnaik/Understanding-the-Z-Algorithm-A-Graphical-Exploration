def getZarr(string, z):
    n = len(string)
    l, r, k = 0, 0, 0
    for i in range(1, n):
        if i > r:
            l, r = i, i
            while r < n and string[r - l] == string[r]:
                r += 1
            z[i] = r - l
            r -= 1
        else:
            k = i - l
            if z[k] < r - i + 1:
                z[i] = z[k]
            else:
                l = i
                while r < n and string[r - l] == string[r]:
                    r += 1
                z[i] = r - l
                r -= 1

def search(file_path):
    try:
        with open(file_path, 'r') as file:
            content = file.read().strip().split('\n')
            text = content[0]
            pattern = content[1]

        # Create concatenated string "P$T"
        concat = pattern + "$" + text
        l = len(concat)

        # Construct Z array
        z = [0] * l
        getZarr(concat, z)

        # now looping through Z array for matching condition
        for i in range(l):

            # if Z[i] (matched region) is equal to pattern
            # length we got the pattern
            if z[i] == len(pattern):
                print("Pattern found at index", i - len(pattern) - 1)

    except FileNotFoundError:
        print("File not found. Please check the file path.")

# Driver Code
# Driver Code
if __name__ == "__main__":
    file_path = input("Enter the path to the file containing both text and pattern: ")
    search(file_path)
