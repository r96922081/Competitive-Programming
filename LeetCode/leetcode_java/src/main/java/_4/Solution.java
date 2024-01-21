package _4;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;

class Solution {
    public double findMedianSortedArrays(int[] nums1, int[] nums2) {
        return 0;
    }

    public static void check(boolean b) {
        if (!b)
            throw new Error("check failed!");
    }

    public void Main() {
        int[] nums1 = null;
        int[] nums2 = null;

        int seed = 2;
        Random random = new Random(seed);
        for (int i = 0; i < 20; i++) {
            List<Integer> list1 = new ArrayList<>();
            List<Integer> list2 = new ArrayList<>();
            int count = 10;
            if (i % 2 == 0)
                count = 9;

            for (int j = 0; j < count; j++) {
                if (j % 2 == 0)
                    list1.add(random.nextInt(20));
                else
                    list2.add(random.nextInt(20));
            }

            Collections.sort(list1);
            Collections.sort(list2);
            nums1 = list1.stream().mapToInt(Integer::intValue).toArray();
            nums2 = list2.stream().mapToInt(Integer::intValue).toArray();

            List<Integer> list3 = new ArrayList<>();
            list3.addAll(list1);
            list3.addAll(list2);
            Collections.sort(list3);

            System.out.println(list1);
            System.out.println(list2);
            System.out.println(list3);

            double median = 0;
            if (list3.size() % 2 == 1)
                median = list3.get(list3.size()/2);
            else
                median = ((double)(list3.get(list3.size()/2) + list3.get(list3.size()/2 - 1)))/2.0;

            System.out.println("median = " + median);

            double myAnswer = findMedianSortedArrays(nums1, nums2);
            System.out.println("myAnswer = " + myAnswer);
            check(median == myAnswer);
        }
    }

    public static void main(String[] args) {
        new Solution().Main();
    }
}