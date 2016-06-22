using System;
using PizzaStore.Pizzas;

namespace PizzaStore.Stores
{
    public abstract class PizzaStore
    {
        public Pizza Order(PizzaType type)
        {
            var pizza = Create(type: type);
            pizza.Prepare();
            pizza.Bake();
            pizza.Cut();
            pizza.Box();
            return pizza;
        }

        protected virtual Pizza Create(PizzaType type)
        {
            switch (type)
            {
                case PizzaType.Cheese:
                    return new CheesePizza();
                case PizzaType.Pepperoni:
                    return new PepperoniPizza();
                case PizzaType.Veggie:
                    return new VeggiePizza();
                case PizzaType.Clam:
                    return new ClamPizza();
                default:
                    throw new ArgumentOutOfRangeException(nameof(type), type, null);
            }
        }
    }
}
