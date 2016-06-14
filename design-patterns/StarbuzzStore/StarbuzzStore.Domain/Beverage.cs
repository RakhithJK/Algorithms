namespace StarbuzzStore.Domain
{
    public abstract class Beverage
    {
        public      virtual string Description   => description;
        public      virtual double Cost { get; } = 0;
        protected           string description;
    }
}
