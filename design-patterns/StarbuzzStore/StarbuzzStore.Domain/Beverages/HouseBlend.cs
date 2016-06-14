namespace StarbuzzStore.Domain.Beverages
{
    public class HouseBlend : Beverage
    {
        public HouseBlend()
        {
            description = "House Blend Coffee";
        }

        public override double Cost { get; } = .89;
    }
}
