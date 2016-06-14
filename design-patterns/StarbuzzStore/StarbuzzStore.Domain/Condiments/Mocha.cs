namespace StarbuzzStore.Domain.Condiments
{
    public class Mocha : CondimentDecorator
    {
        public Mocha(Beverage beverage)
        {
            this.beverage = beverage;
        }
        private readonly Beverage   beverage;
        public override string      Description => $"{beverage.Description}, Mocha";
        public override double      Cost => beverage.Cost + .20;
    }
}