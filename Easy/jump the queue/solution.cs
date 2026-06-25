using System;
using System.Linq;
using System.IO;
using System.Text;
using System.Collections;
using System.Collections.Generic;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
class Solution
{
    static void Main(string[] args)
    {
        string[] inputs;
        inputs = Console.ReadLine().Split(' ');
        int g = int.Parse(inputs[0]);
        int e = int.Parse(inputs[1]);

        List<List<int>> friendGroups = new List<List<int>>();

        for (int i = 0; i < g; i++)
        {
            string group = Console.ReadLine();
            List<int> parsedGroups = group.Split(' ', StringSplitOptions.RemoveEmptyEntries)
                                .Select(int.Parse)
                                .ToList();

            friendGroups.Add(parsedGroups);
        }

        List<int> lunchQueue = new List<int>();
        inputs = Console.ReadLine().Split(' ');
        for (int i = 0; i < e; i++)
        {
            int _event = int.Parse(inputs[i]);
            int belongsTo = -1;
            if (_event != -1) {
                for (int index = 0; index < friendGroups.Count(); index++) {
                    if (friendGroups[index].Contains(_event)) {
                        belongsTo = index;
                        break;
                    }
                }
                if (belongsTo != -1) {
                    int aFriendIsInQueue = lunchQueue.FindLastIndex(x => friendGroups[belongsTo].Contains(x));
                    if (aFriendIsInQueue != -1) {
                        lunchQueue.Insert(aFriendIsInQueue + 1, _event);
                    }
                    else {
                        lunchQueue.Add(_event);
                    }
                }
                else {
                    lunchQueue.Add(_event);
                }
            }
            else {
              if (lunchQueue.Count() > 0) {
                Console.WriteLine(lunchQueue[0]);
                lunchQueue.RemoveAt(0);
              }
            }
        }
    }
}