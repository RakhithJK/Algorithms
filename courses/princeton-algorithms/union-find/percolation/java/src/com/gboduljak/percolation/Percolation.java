import edu.princeton.cs.algs4.WeightedQuickUnionUF;

public class Percolation {

    public Percolation(int n) {
        this.n = n;
        ensureNIsPositive();

        this.grid          = new boolean[n][n];
        this.graph         = new WeightedQuickUnionUF(n * n + 2);
        this.virtualTop    = 0;
        this.virtualBottom = n * n + 1;
    }

    private int                  n;
    private boolean[][]          grid;
    private int                  virtualTop;
    private int                  virtualBottom;
    private WeightedQuickUnionUF graph;

    public void open(int row, int column) {
        int siteToOpenRowIndex    = row - 1;
        int siteToOpenColumnIndex = column - 1;

        int leftNeighbourColumn  = column - 1;
        int rightNeighbourColumn = column + 1;
        int aboveNeighbourRow    = row + 1;
        int belowNeighbourRow    = row - 1;

        int siteToOpenVertex         = mapCoordsToVertex(row, column);
        int leftNeighbourSiteVertex  = mapCoordsToVertex(row, leftNeighbourColumn);
        int rightNeighbourSiteVertex = mapCoordsToVertex(row, rightNeighbourColumn);
        int belowNeighbourSiteVertex = mapCoordsToVertex(belowNeighbourRow, column);
        int aboveNeighbourSiteVertex = mapCoordsToVertex(aboveNeighbourRow, column);

        grid[siteToOpenRowIndex][siteToOpenColumnIndex] = true;

        if (column > 1 && isOpen(row, leftNeighbourColumn))
            graph.union(siteToOpenVertex, leftNeighbourSiteVertex);

        if (column < n && isOpen(row, rightNeighbourColumn))
            graph.union(siteToOpenVertex, rightNeighbourSiteVertex);

        if (row > 1 && isOpen(belowNeighbourRow, column))
            graph.union(siteToOpenVertex, belowNeighbourSiteVertex);

        if (row < n && isOpen(aboveNeighbourRow, column))
            graph.union(siteToOpenVertex, aboveNeighbourSiteVertex);

        if (row == 1)
            graph.union(mapCoordsToVertex(row, column), virtualTop);
        if (row == n)
            graph.union(mapCoordsToVertex(row, column), virtualBottom);

    }

    public boolean percolates() {
        return graph.connected(virtualTop, virtualBottom);
    }

    public boolean isOpen(int row, int column) {
        return grid[row - 1][column - 1];
    }

    public boolean isFull(int row, int column) {
        return graph.connected(mapCoordsToVertex(row, column), virtualTop);
    }

    private void ensureNIsPositive() {
        if(this.n <= 0)
            throw new IllegalArgumentException();
    }

    private int mapCoordsToVertex(int row, int column) {
        return this.n * (row - 1) + column;
    }
}