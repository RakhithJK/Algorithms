using System;
using System.Collections.Generic;
using System.Linq;

namespace MagicBridges
{
    public class Solver
    {

        public Solver(int numberOfTowers, int numberOfFloors, IEnumerable<Bridge> bridges)
        {
            this.numberOfTowers = numberOfTowers;
            this.numberOfFloors = numberOfFloors;
            this.numberOfBridges = bridges.Count();
            this.floorsCount = numberOfTowers * numberOfFloors * numberOfBridges;

            floorsMatrix = new int[floorsCount, floorsCount];

            for (int tower = 0; tower < numberOfTowers; tower++)
            {
                var towerFirstFloorId = ComposeFloorTowerId(tower, 0);
                var adjacentTowerFirstFloorId = ComposeFloorTowerId(tower + 1, 0);

                floorsMatrix[towerFirstFloorId, adjacentTowerFirstFloorId] = 1;
                floorsMatrix[adjacentTowerFirstFloorId, towerFirstFloorId] = 1;
            }

            foreach (var bridge in bridges)
            {
                var sourceTowerFloorId = ComposeFloorTowerId(bridge.SourceTower, bridge.SourceTowerFloor);
                var destinationTowerFloorId = ComposeFloorTowerId(bridge.DestinationTower, bridge.DestinationTowerFloor);
                floorsMatrix[sourceTowerFloorId, destinationTowerFloorId] = bridge.Cost;
                floorsMatrix[destinationTowerFloorId, sourceTowerFloorId] = bridge.Cost;
            }

        }

        private int numberOfTowers;
        private int numberOfFloors;
        private int numberOfBridges;
        private int floorsCount;

        private int ComposeFloorTowerId(int tower, int floor) => int.Parse($"{tower}{floor}");
        private int[,] floorsMatrix;

        // Floyd-Warshall
        private void ComputeShortestPaths()
        {
            for (int i = 0; i < floorsCount; i++)
            {
                for (int j = 0; j < floorsCount; j++)
                {
                    for (int k = 0; k < floorsCount; k++)
                    {
                        if (floorsMatrix[i, j] > floorsMatrix[i, k] + floorsMatrix[k, j])
                        {
                            floorsMatrix[i,j] = floorsMatrix[i,k] + floorsMatrix[k,j];
                        }
                    }
                }
            }
        }

        public int GetCost(int sourceTower, int sourceTowerFloor, int destinationTower, int destinationTowerFloor)
            =>
            floorsMatrix[
                ComposeFloorTowerId(sourceTower - 1, sourceTowerFloor - 1),
                ComposeFloorTowerId(destinationTower - 1, destinationTowerFloor - 1)];

        public class Bridge
        {
            public Bridge(int sourceTower, int sourceTowerFloor, int destinationTower, int destinationTowerFloor, int cost)
            {
                this.SourceTower = sourceTower - 1;
                this.SourceTowerFloor = sourceTowerFloor - 1;
                this.DestinationTower = destinationTower - 1;
                this.DestinationTowerFloor = destinationTowerFloor - 1;
                this.Cost = cost;
            }
            public int SourceTower { get; set; }
            public int SourceTowerFloor { get; set; }

            public int DestinationTower { get; set; }
            public int DestinationTowerFloor { get; set; }
            public int Cost { get; set; }
        }
    }
}
