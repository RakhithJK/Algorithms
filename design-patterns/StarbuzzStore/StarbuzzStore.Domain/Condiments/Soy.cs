namespace StarbuzzStore.Domain.Condiments
{
    public class Soy : CondimentDecorator
    {
        public Soy(Beverage beverage)
        {
            this.beverage = beverage;
        }
        private readonly Beverage   beverage;
        public override string      Description => $"{beverage.Description}, Soy";
        public override double      Cost => beverage.Cost + .40;
    }
}