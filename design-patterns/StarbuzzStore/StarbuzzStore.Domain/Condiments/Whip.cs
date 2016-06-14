namespace StarbuzzStore.Domain.Condiments
{
    public class Whip : CondimentDecorator
    {
        public Whip(Beverage beverage)
        {
            this.beverage = beverage;
        }
        private readonly Beverage   beverage;
        public override string      Description => $"{beverage.Description}, Whip";
        public override double      Cost => beverage.Cost + .30;
    }
}