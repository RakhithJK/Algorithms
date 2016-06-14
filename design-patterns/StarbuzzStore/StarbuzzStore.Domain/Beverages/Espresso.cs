namespace StarbuzzStore.Domain.Beverages
{
    public class Espresso : Beverage
    {
        public Espresso()
        {
            description = "Espresso";
        }

        public override double Cost { get; } = 1.99;
    }
}
