using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Threading.Channels;

namespace task6
{
    class Program
    {
        static string[] AllSubsets(string[] set)
        {   
            int amount = 0;
            int lenght = set.Length;
            amount = (int) Math.Pow(2, lenght);
            string[] allsubs = new string[amount];
                for (int i = 0; i <amount ; i++)
                {
                    allsubs[i] = "{";
                    for (int j = 0; j < lenght; j++)
                        if ((i & (1 << j)) > 0)
                            allsubs[i] += set[j];
                    allsubs[i] += "}";
                }

                return allsubs;
        }

        static List<string> KLenghtSubs(int k, string[] set)
        {
            List<string> result = new List<string>();
            for (int i = 0; i < set.Length; i++)
            {
                if ((set[i].Length - 2) == k)
                {
                    result.Add(set[i]);
                }
            }

            return result;
        }


        static List<string> SubWithElement(char el, string[] set)
        {  
            List<string> result = new List<string>();
            for (int i = 0; i < set.Length; i++)
            {
                if (set[i].Contains(el))
                    result.Add(set[i]);
            }

            return result;
        }
        
        static void Main(string[] args)
        {
            bool check = true;
            while (check)
            {
                Console.WriteLine("Enter elements of integer set:");
                string elems = Console.ReadLine();
                string[] temp = elems.Split(new Char[] {' '});
                int lenght = (int) Math.Pow(2, temp.Length);
                string[] Alls = new string[lenght];
                Console.Write(
                    "type 1 - for all subsets, 2 - for k-lenght subsets and 3 for subset with your element: ");
                int chose = int.Parse(Console.ReadLine());
                Alls = AllSubsets(temp);
                
                if (chose == 1)
                {
                    for (int i = 0; i < lenght; i++)
                        Console.WriteLine(Alls[i]);
                }
                    

                if (chose == 2)
                {
                    Console.Write("Enter lenght: ");
                    int k = int.Parse(Console.ReadLine());
                    List<string> ksubs = new List<string>();
                    ksubs = KLenghtSubs(k, Alls);
                    if (ksubs.Count == 1)
                        Console.WriteLine(ksubs[0]);

                    else if (ksubs.Count > 1)
                        for (int i = 0; i < ksubs.Count; i++)
                            Console.WriteLine(ksubs[i]);
                    else
                        Console.WriteLine("element with such lenght not found:(");
                }

                if (chose == 3)
                {
                    Console.Write("Enter element you looking for: ");
                    char el = Convert.ToChar(Console.ReadLine());
                    List<string> SubWithEl = new List<string>();
                    SubWithEl = SubWithElement(el, Alls);
                    if (SubWithEl.Count == 0)
                        Console.WriteLine("Element is not found:(");
                    for (int i = SubWithEl.Count - 1; i > 0; i--)
                        Console.WriteLine(SubWithEl[i]);
                }


                else if(chose<=0 || chose>3)
                {
                    Console.WriteLine("something is wrong, try again");
                    System.Threading.Thread.Sleep(1100);
                    Console.Clear();
                }

                Console.WriteLine("If you want to start again - type 1, else - type 2");
                int restart = int.Parse(Console.ReadLine());
                if (restart == 1) Console.Clear();
                else if (restart == 2)
                {
                    Console.WriteLine("Thx, goodbye:)");
                    check = false;
                }
            }
        }
    }
}