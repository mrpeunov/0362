using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Threading;

namespace task7_
{
    class Program
    {
        public class Node
        {
            public char Symbol { get; set; }
            public int Frequency { get; set; }
            public Node Right { get; set; }
            public Node Left { get; set; }

            public List<bool> Traverse(char symbol, List<bool> data, Dictionary<char, List<bool>> Table)
            {
                
                if (Right == null && Left == null)
                {
                    if (symbol.Equals(this.Symbol))
                    {
                        int count = 0;
                        foreach (var i in Table)
                        {
                            if (!symbol.Equals(i.Key))
                                count++;
                        }
                        if (count == Table.Count)
                            Table.Add(symbol, data);
                        return data;
                    }
                    else
                    {
                        return null;
                    }
                }
                else
                {
                    List<bool> left = null;
                    List<bool> right = null;

                    if (Left != null)
                    {
                        List<bool> leftPath = new List<bool>();
                        leftPath.AddRange(data);
                        leftPath.Add(false);

                        left = Left.Traverse(symbol, leftPath, Table);
                    }

                    if (Right != null)
                    {
                        List<bool> rightPath = new List<bool>();
                        rightPath.AddRange(data);
                        rightPath.Add(true);
                        right = Right.Traverse(symbol, rightPath,Table);
                    }

                    if (left != null)
                    {
                        return left;
                    }
                    else
                    {
                        return right;
                    }
                }
            }

            
        }
        public class HuffmanTree
    {
        
        private List<Node> nodes = new List<Node>();
        public Node Root { get; set; }
       
        
        public void Build(Dictionary<char, int> Table)
        {

            foreach (KeyValuePair<char, int> symbol in Table)
            {
                nodes.Add(new Node() { Symbol = symbol.Key, Frequency = symbol.Value });
            }

            while (nodes.Count > 1)
            {
                List<Node> orderedNodes = nodes.OrderBy(node => node.Frequency).ToList<Node>();

                if (orderedNodes.Count >= 2)
                {
                  
                    List<Node> taken = orderedNodes.Take(2).ToList<Node>();

                    
                    Node parent = new Node()
                    {
                        Symbol = '*',
                        Frequency = taken[0].Frequency + taken[1].Frequency,
                        Left = taken[0],
                        Right = taken[1]
                    };

                    nodes.Remove(taken[0]);
                    nodes.Remove(taken[1]);
                    nodes.Add(parent);
                }

                this.Root = nodes.FirstOrDefault();

            }

        }

        public BitArray Encode(string source)
        {
            Dictionary<char, List<bool>> encodedTable = new Dictionary<char, List<bool>>();
            List<bool> encodedSource = new List<bool>();

            for (int i = 0; i < source.Length; i++)
            {
                List<bool> encodedSymbol = this.Root.Traverse(source[i], new List<bool>(), encodedTable);
                encodedSource.AddRange(encodedSymbol);
            }

            BitArray bits = new BitArray(encodedSource.ToArray());


            foreach (KeyValuePair<char, List<bool>> symbol in encodedTable)
            {
                Console.Write($"Num = {symbol.Key} --- ");
                foreach (var i in symbol.Value)
                {
                    if(i)
                        Console.Write("1");
                    else 
                        Console.Write("0");
                }

                Console.WriteLine();
            }
            
            return bits;
        }

        public string Decode(BitArray bits)
        {
            Node current = this.Root;
            string decoded = "";

            foreach (bool bit in bits)
            {
                if (bit)
                {
                    if (current.Right != null)
                    {
                        current = current.Right;
                    }
                }
                else
                {
                    if (current.Left != null)
                    {
                        current = current.Left;
                    }
                }

                if (IsLeaf(current))
                {
                    decoded += current.Symbol;
                    current = this.Root;
                }
            }

            return decoded;
        }

        public bool IsLeaf(Node node)
        {
            return (node.Left == null && node.Right == null);
        }
        static void Main(string[] args)
        {
            Dictionary<char, int> Table = new Dictionary<char, int>();
            char temp;
            int temp_fr;
            string input;
            Console.Write("Enter symbol: ");
            temp = Console.ReadKey().KeyChar;
            while (temp != '\r')
            {
                Console.Write("\nEnter frequency: ");
                temp_fr = int.Parse(Console.ReadLine());
                Table.Add(temp, temp_fr);
                Console.Write("Enter symbol: ");
                temp = Console.ReadKey().KeyChar;
            }
            Console.Clear();
            HuffmanTree huffmanTree = new HuffmanTree();
            
            huffmanTree.Build(Table);
            Console.Write("\nEnter message: ");
            input = Console.ReadLine();
            
             BitArray encoded = huffmanTree.Encode(input);
            
             Console.Write("Encoded: ");
             foreach (bool bit in encoded)
             {
                 Console.Write((bit ? 1 : 0) + "");
             }
             Console.WriteLine();

            
             string decoded = huffmanTree.Decode(encoded);
            
             Console.WriteLine("Decoded: " + decoded);
            
             Console.ReadLine();
             Console.WriteLine("Good bye :*");
        }
    }
    }
}