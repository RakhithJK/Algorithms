using System;
using PizzaStore.Pizzas;

namespace PizzaStore.Stores
{
    public interface IPizzaStore
    {
        Pizza Order(PizzaType type);
        Pizza Create(PizzaType type);
    }
    public abstract class PizzaStore : IPizzaStore
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

        public virtual Pizza Create(PizzaType type)
        {
            throw new NotImplementedException();
        }
    }
}
