import { toSafeFileName } from "./service";

test('toSafeFileName', () => {
    expect(toSafeFileName('a')).toBe('a');
    expect(toSafeFileName('../a')).toBe('a');
    expect(toSafeFileName('..\\a')).toBe('a');
    expect(toSafeFileName('../..\\a')).toBe('a');
    expect(toSafeFileName('../c/..\\a')).toBe('c/a');
});