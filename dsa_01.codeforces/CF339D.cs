namespace dsa_01.codeforces
{
    public class CF339D
    {
        
        internal static bool Refresh_SegmentTree(
            int[] tree,
            int[] arr, 
            int treeIndex,
            int arrIndex,
            int rangeLeft,
            int rangeRight)
        {
            if (rangeLeft == rangeRight)
            {
                tree[treeIndex] = arr[rangeLeft];
                return true;
            }
            
            int mid = (rangeLeft + rangeRight) / 2;
            bool belowLevelOperation;

            if (arrIndex <= mid)
            {
                belowLevelOperation = Refresh_SegmentTree(
                    tree,
                    arr,
                    treeIndex * 2 + 1,
                    arrIndex,
                    rangeLeft,
                    mid);
            }
            else
            {
                belowLevelOperation = Refresh_SegmentTree(
                    tree,
                    arr,
                    treeIndex * 2 + 2,
                    arrIndex,
                    mid + 1,
                    rangeRight);
            }

            if (belowLevelOperation)
            {
                tree[treeIndex] = tree[treeIndex * 2 + 1] | tree[treeIndex * 2 + 2];
            }
            else
            {
                tree[treeIndex] = tree[treeIndex * 2 + 1] ^ tree[treeIndex * 2 + 2];
            }

            return !belowLevelOperation;
        }

        static bool Build_SegmentTree(
            int[] tree,
            int[] arr,
            int treeIndex,
            int queryLeft,
            int queryRight)
        {
            if (queryLeft == queryRight)
            {
                tree[treeIndex] = arr[queryLeft];
                return true;
            }

            int mid = (queryRight + queryLeft) >> 1;

            var belowOp = Build_SegmentTree(
                tree, 
                arr,
                treeIndex * 2 + 1,
                queryLeft,
                mid);

            Build_SegmentTree(
                tree,
                arr,
                treeIndex * 2 + 2,
                mid + 1,
                queryRight);

            tree[treeIndex] =
                belowOp
                ? (tree[treeIndex * 2 + 1] | tree[treeIndex * 2 + 2])
                : (tree[treeIndex * 2 + 1] ^ tree[treeIndex * 2 + 2]);

            return !belowOp;
        }

        public static void Main(string[] args)
        {
            string[] _line;
            int n, m;

            _line = Console.ReadLine()?.Split(" ") ?? [];

            n = int.Parse(_line[0]);
            m = int.Parse(_line[1]);

            int[] arr = new int[1 << n];

            _line = Console.ReadLine()?.Split(" ") ?? [];

            for (int i = 0; i < arr.Length; i++)
            {
                arr[i] = int.Parse(_line[i]);
            }

            int[] tree = new int[4 * arr.Length];

            Build_SegmentTree(
                tree,
                arr,
                0,
                0,
                arr.Length - 1);

            for (int i = 0; i < m; ++i)
            {
                _line = Console.ReadLine()?.Split(" ") ?? [];
                int p = int.Parse(_line[0]);
                int v = int.Parse(_line[1]);

                arr[p - 1] = v;

                Refresh_SegmentTree(
                    tree,
                    arr,
                    0,
                    p - 1,
                    0,
                    arr.Length - 1);

                Console.WriteLine(tree[0]);
            }
        }
    }
}
