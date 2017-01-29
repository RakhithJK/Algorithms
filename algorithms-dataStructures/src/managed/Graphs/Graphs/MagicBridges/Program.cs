namespace MagicBridges
{
    class Program
    {
        static void Main(string[] args)
        {
            var bridges = new[]
            {
                new Solver.Bridge(1,3,2,4,3),
                new Solver.Bridge(2,3,3,3,2),
                new Solver.Bridge(3,4,5,3,1)   
            };
            var solution = new Solver(5,4, bridges);

            var t1 = solution.GetCost(1, 3, 2, 3);

        }
    }
}