package _2;

class Solution {
    public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        return null;
    }

    public static class ListNode {
        int val;
        ListNode next;
        ListNode() {}
        ListNode(int val) { this.val = val; }
        ListNode(int val, ListNode next) { this.val = val; this.next = next; }
    }

    public static void check(boolean b) {
        if (!b)
            throw new Error("check failed!");
    }
    public static void main(String[] args) {
        ListNode l1 = new ListNode()
        check(false);
    }
}