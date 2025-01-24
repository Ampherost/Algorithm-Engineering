import quicksort

class Submission(quicksort.QSortBase):
    def pivot(self, lo, hi, depth, breadth):
        # The median of the low, middle, and high will be chosen as the pivot
        
        a = self.array[lo]
        b = self.array[(lo + hi) // 2]
        c = self.array[hi]
        
        # We return the median using comparisons
        if a > b:
            if b > c:
                return b
            elif a > c:
                return c
            else:
                return a
        else:
            if a > c:
                return a
            elif b > c:
                return c
            else:
                return b
