using System;

using PizzaStore.Pizzas;
using chicago = PizzaStore.Pizzas.Chicago;
using newYork = PizzaStore.Pizzas.NewYork;

namespace PizzaStore.Stores
{
    public class ChicagoPizzaStore : PizzaStore
    {
        protected override Pizza Create(PizzaType type)
        {
            switch (type)
            {
                case PizzaType.Cheese:
                    return new chicago::CheesePizza();
                case PizzaType.Pepperoni:
                    return new chicago::PepperoniPizza();
                case PizzaType.Veggie:
                    return new chicago::VeggiePizza();
                case PizzaType.Clam:
                    return new chicago::ClamPizza();
                default:
                    throw new ArgumentOutOfRangeException(nameof(type), type, null);
            }
        }   
    }
    public class NewYorkPizzaStore : PizzaStore
    {
        protected override Pizza Create(PizzaType type)
        {
            switch (type)
            {
                case PizzaType.Cheese:
                    return new newYork::CheesePizza();
                case PizzaType.Pepperoni:
                    return new newYork::PepperoniPizza();
                case PizzaType.Veggie:
                    return new newYork::VeggiePizza();
                case PizzaType.Clam:
                    return new newYork::ClamPizza();
                default:
                    throw new ArgumentOutOfRangeException(nameof(type), type, null);
            }
        }
    }
}